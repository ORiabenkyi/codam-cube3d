#include "cube3d.h"

/*
** Reads one RGBA pixel from a texture at (x, y) and returns it as uint32_t.
** MLX42 stores pixels as [R, G, B, A] bytes (4 bytes per pixel).
*/
static uint32_t	tex_pixel(mlx_texture_t *t, int x, int y)
{
	int	idx;

	idx = (y * (int)t->width + x) * (int)t->bytes_per_pixel;
	return ((t->pixels[idx] << 24) | (t->pixels[idx + 1] << 16)
		| (t->pixels[idx + 2] << 8) | t->pixels[idx + 3]);
}

/*
** Halves each RGB channel independently (no cross-channel bit leakage).
** Alpha is kept at 0xFF.  Used to darken closed-door textures.
*/
static uint32_t	darken(uint32_t c)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = ((c >> 24) & 0xFF) >> 1;
	g = ((c >> 16) & 0xFF) >> 1;
	b = ((c >> 8)  & 0xFF) >> 1;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/*
** Converts a t_color into a packed RGBA uint32_t (alpha = 0xFF).
*/
static uint32_t	color_to_rgba(t_color c)
{
	return ((c.r << 24) | (c.g << 16) | (c.b << 8) | 0xFF);
}

/*
** Initialises ray direction and DDA step values for screen column x.
** camera_x maps [0, SCREEN_W-1] to [-1, +1] (left to right).
*/
static void	init_ray(t_game *game, t_ray *ray, int x)
{
	t_player	*p;

	p = &game->player;
	ray->is_door = 0;
	ray->cam_x = 2.0 * x / SCREEN_W - 1.0;
	ray->dir_x = p->dir_x + p->plane_x * ray->cam_x;
	ray->dir_y = p->dir_y + p->plane_y * ray->cam_x;
	ray->map_x = (int)p->pos_x;
	ray->map_y = (int)p->pos_y;
	ray->ddist_x = (ray->dir_x == 0) ? 1e30 : fabs(1.0 / ray->dir_x);
	ray->ddist_y = (ray->dir_y == 0) ? 1e30 : fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sdist_x = (p->pos_x - ray->map_x) * ray->ddist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sdist_x = (ray->map_x + 1.0 - p->pos_x) * ray->ddist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sdist_y = (p->pos_y - ray->map_y) * ray->ddist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sdist_y = (ray->map_y + 1.0 - p->pos_y) * ray->ddist_y;
	}
}

/*
** Digital Differential Analysis: steps through the grid until a solid cell
** is hit ('1' wall or closed 'D' door).
** Sets ray->side: 0 if hit on X axis, 1 if hit on Y axis.
** Sets ray->is_door: 1 if the stopping cell is a door (for darker rendering).
** Open doors ('D' with state DOOR_OPEN) are transparent — ray continues.
*/
static void	dda(t_game *game, t_ray *ray)
{
	char		**grid;
	int			rows;
	int			col_len;
	char		cell;
	t_door		*door;

	grid = game->map.grid;
	rows = game->map.rows;
	while (1)
	{
		if (ray->sdist_x < ray->sdist_y)
		{
			ray->sdist_x += ray->ddist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sdist_y += ray->ddist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= rows || ray->map_x < 0)
			break ;
		col_len = (int)ft_strlen(grid[ray->map_y]);
		if (ray->map_x >= col_len)
			break ;
		cell = grid[ray->map_y][ray->map_x];
		if (cell == '1')
			break ;
		if (cell == 'D')
		{
			door = find_door(&game->map, ray->map_x, ray->map_y);
			if (!door || door->state == DOOR_CLOSED)
			{
				ray->is_door = 1;
				break ;
			}
			/* DOOR_OPEN: ray passes through */
		}
	}
}

/*
** Computes perpendicular wall distance, wall height on screen, and which
** texture column to sample.
**
** Texture selection (coordinate system: X=east+, Y=south+):
**   side==0, step_x>0  → ray went east, hit WEST face  → WE texture
**   side==0, step_x<0  → ray went west, hit EAST face  → EA texture
**   side==1, step_y>0  → ray went south, hit NORTH face → NO texture
**   side==1, step_y<0  → ray went north, hit SOUTH face → SO texture
*/
static void	calc_wall(t_game *game, t_ray *ray)
{
	t_player		*p;
	double			wall_x;
	mlx_texture_t	*tex;

	p = &game->player;
	if (ray->side == 0)
		ray->wall_dist = ray->sdist_x - ray->ddist_x;
	else
		ray->wall_dist = ray->sdist_y - ray->ddist_y;
	ray->line_h = (int)(SCREEN_H / ray->wall_dist);
	ray->draw_start = -ray->line_h / 2 + SCREEN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + SCREEN_H / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
	if (ray->side == 0)
		ray->tex_idx = (ray->step_x > 0) ? TEX_WE : TEX_EA;
	else
		ray->tex_idx = (ray->step_y > 0) ? TEX_NO : TEX_SO;
	if (ray->side == 0)
		wall_x = p->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = p->pos_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex = game->tex[ray->tex_idx];
	ray->tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = (int)tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = (int)tex->width - ray->tex_x - 1;
}

/*
** Draws one vertical screen column:
**   - ceiling color above the wall
**   - textured wall strip
**   - floor color below the wall
*/
static void	draw_column(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	double			step;
	double			tex_pos;
	int				tex_y;
	uint32_t		ceil_col;
	uint32_t		floor_col;
	int				y;

	tex = game->tex[ray->tex_idx];
	step = (double)tex->height / ray->line_h;
	tex_pos = (ray->draw_start - SCREEN_H / 2 + ray->line_h / 2) * step;
	ceil_col = color_to_rgba(game->map.ceiling);
	floor_col = color_to_rgba(game->map.floor);
	y = 0;
	while (y < SCREEN_H)
	{
		if (y < ray->draw_start)
			mlx_put_pixel(game->image, x, y, ceil_col);
		else if (y > ray->draw_end)
			mlx_put_pixel(game->image, x, y, floor_col);
		else
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)tex->height)
				tex_y = (int)tex->height - 1;
			tex_pos += step;
			if (ray->is_door)
				mlx_put_pixel(game->image, x, y,
					darken(tex_pixel(tex, ray->tex_x, tex_y)));
			else
				mlx_put_pixel(game->image, x, y,
					tex_pixel(tex, ray->tex_x, tex_y));
		}
		y++;
	}
}

/*
** Main render function — called every frame.
** Casts one ray per screen column and draws the result.
*/
void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(game, &ray, x);
		dda(game, &ray);
		calc_wall(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}
