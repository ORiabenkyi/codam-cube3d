#include "cube3d.h"

/*
** Local projection data for one sprite.
** tx = camera-space horizontal offset, ty = camera-space depth.
*/
typedef struct s_sproj
{
	double	tx;
	double	ty;
	int		screen_x;
	int		h;
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
}	t_sproj;

/*
** Reads one RGBA pixel from a sprite texture at (x, y).
*/
static uint32_t	sp_pix(mlx_texture_t *t, int x, int y)
{
	int	idx;

	idx = (y * (int)t->width + x) * (int)t->bytes_per_pixel;
	return ((t->pixels[idx] << 24) | (t->pixels[idx + 1] << 16)
		| (t->pixels[idx + 2] << 8) | t->pixels[idx + 3]);
}

/*
** Projects sprite s into camera space and fills p.
** Returns 1 if visible (in front of camera), 0 if behind.
*/
static int	project_sprite(t_game *game, t_sprite *s, t_sproj *p)
{
	t_player	*pl;
	double		rel_x;
	double		rel_y;
	double		inv_det;

	pl = &game->player;
	rel_x = s->x - pl->pos_x;
	rel_y = s->y - pl->pos_y;
	inv_det = 1.0 / (pl->plane_x * pl->dir_y - pl->dir_x * pl->plane_y);
	p->tx = inv_det * (pl->dir_y * rel_x - pl->dir_x * rel_y);
	p->ty = inv_det * (-pl->plane_y * rel_x + pl->plane_x * rel_y);
	if (p->ty <= 0.01)
		return (0);
	p->screen_x = (int)((SCREEN_W / 2) * (1.0 + p->tx / p->ty));
	p->h = abs((int)(SCREEN_H / p->ty));
	p->start_y = -p->h / 2 + SCREEN_H / 2;
	if (p->start_y < 0)
		p->start_y = 0;
	p->end_y = p->h / 2 + SCREEN_H / 2;
	if (p->end_y >= SCREEN_H)
		p->end_y = SCREEN_H - 1;
	p->start_x = -p->h / 2 + p->screen_x;
	p->end_x = p->h / 2 + p->screen_x;
	return (1);
}

/*
** Draws one vertical stripe of a sprite at screen column stripe.
** Skips fully transparent pixels (alpha == 0).
*/
static void	draw_sprite_col(t_sproj *p, mlx_texture_t *t,
	mlx_image_t *img, int stripe)
{
	int			tex_x;
	int			y;
	int			tex_y;
	uint32_t	color;

	tex_x = (stripe - (p->screen_x - p->h / 2)) * (int)t->width / p->h;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)t->width)
		tex_x = (int)t->width - 1;
	y = p->start_y;
	while (y <= p->end_y)
	{
		tex_y = (y - SCREEN_H / 2 + p->h / 2) * (int)t->height / p->h;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)t->height)
			tex_y = (int)t->height - 1;
		color = sp_pix(t, tex_x, tex_y);
		if ((color & 0xFF) != 0)
			mlx_put_pixel(img, stripe, y, color);
		y++;
	}
}

/*
** Insertion sort: reorders order[] and dist[] so that dist is descending
** (farthest sprite first — painter's algorithm for sprite-on-sprite overdraw).
*/
static void	sort_by_dist(int *order, double *dist, int n)
{
	int		i;
	int		j;
	int		tmp_o;
	double	tmp_d;

	i = 1;
	while (i < n)
	{
		tmp_o = order[i];
		tmp_d = dist[i];
		j = i - 1;
		while (j >= 0 && dist[j] < tmp_d)
		{
			order[j + 1] = order[j];
			dist[j + 1] = dist[j];
			j--;
		}
		order[j + 1] = tmp_o;
		dist[j + 1] = tmp_d;
		i++;
	}
}

/*
** Renders one sprite (by index) using the current animation frame texture.
** Clips to screen bounds and respects the z-buffer.
*/
static void	draw_one(t_game *game, double *zbuf, int idx)
{
	t_sproj			proj;
	mlx_texture_t	*tex;
	int				stripe;

	tex = game->sp_tex[game->sp_frame];
	if (!tex || !project_sprite(game, &game->map.sprites[idx], &proj))
		return ;
	stripe = proj.start_x;
	while (stripe <= proj.end_x)
	{
		if (stripe >= 0 && stripe < SCREEN_W && proj.ty < zbuf[stripe])
			draw_sprite_col(&proj, tex, game->image, stripe);
		stripe++;
	}
}

/*
** Squared distance between sprite i and the player (for sorting).
*/
static double	sprite_dist2(t_map *map, t_player *p, int i)
{
	double	dx;
	double	dy;

	dx = map->sprites[i].x - p->pos_x;
	dy = map->sprites[i].y - p->pos_y;
	return (dx * dx + dy * dy);
}

/*
** Allocates per-frame order/dist arrays, sorts sprites far-to-near,
** then draws each one.  Returns silently if no sprites or no SP frames.
*/
void	draw_sprites(t_game *game, double *zbuf)
{
	int		n;
	int		*order;
	double	*dist;
	int		i;

	n = game->map.sprite_count;
	if (n == 0 || game->map.sp_count == 0)
		return ;
	order = ft_calloc(n, sizeof(int));
	dist = ft_calloc(n, sizeof(double));
	if (!order || !dist)
	{
		free(order);
		free(dist);
		return ;
	}
	i = 0;
	while (i < n)
	{
		order[i] = i;
		dist[i] = sprite_dist2(&game->map, &game->player, i);
		i++;
	}
	sort_by_dist(order, dist, n);
	i = 0;
	while (i < n)
		draw_one(game, zbuf, order[i++]);
	free(order);
	free(dist);
}

/*
** Advances the sprite animation frame counter once per (1/SPRITE_FPS) seconds.
** No-op if there is only one frame (static sprite) or none.
*/
void	update_sprites(t_game *game)
{
	if (game->map.sp_count <= 1)
		return ;
	game->sp_timer += game->mlx->delta_time;
	if (game->sp_timer >= 1.0 / SPRITE_FPS)
	{
		game->sp_timer -= 1.0 / SPRITE_FPS;
		game->sp_frame = (game->sp_frame + 1) % game->map.sp_count;
	}
}
