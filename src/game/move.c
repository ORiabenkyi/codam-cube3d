#include "cube3d.h"

/*
** Returns 1 if grid cell (nx, ny) is walkable.
** A closed door that the player currently occupies is treated as walkable
** so they can always exit even if they managed to close it from inside.
*/
static int	cell_walkable(t_game *game, int nx, int ny)
{
	char	c;
	t_door	*door;

	if (ny < 0 || nx < 0 || ny >= game->map.rows)
		return (0);
	if (nx >= (int)ft_strlen(game->map.grid[ny]))
		return (0);
	c = game->map.grid[ny][nx];
	if (c == '1' || c == ' ')
		return (0);
	if (c == 'D' || c == 'H')
	{
		door = find_door(&game->map, nx, ny);
		if (!door || door->state == DOOR_OPEN)
			return (1);
		return ((int)game->player.pos_x == nx
			&& (int)game->player.pos_y == ny);
	}
	return (1);
}

/*
** Checks all four corners of the player's bounding box (PLAYER_MARGIN radius)
** to prevent the player from visually clipping into walls.
*/
static int	can_move(t_game *game, double new_x, double new_y)
{
	return (cell_walkable(game, (int)(new_x - PLAYER_MARGIN),
			(int)(new_y - PLAYER_MARGIN))
		&& cell_walkable(game, (int)(new_x + PLAYER_MARGIN),
			(int)(new_y - PLAYER_MARGIN))
		&& cell_walkable(game, (int)(new_x - PLAYER_MARGIN),
			(int)(new_y + PLAYER_MARGIN))
		&& cell_walkable(game, (int)(new_x + PLAYER_MARGIN),
			(int)(new_y + PLAYER_MARGIN)));
}

/*
** Moves the player forward (positive speed) or backward (negative speed)
** along their direction vector.  X and Y are checked independently to
** allow sliding along walls.
*/
static void	move_forward(t_game *game, double speed)
{
	t_player	*p;

	p = &game->player;
	if (can_move(game, p->pos_x + p->dir_x * speed, p->pos_y))
		p->pos_x += p->dir_x * speed;
	if (can_move(game, p->pos_x, p->pos_y + p->dir_y * speed))
		p->pos_y += p->dir_y * speed;
}

/*
** Strafes the player left (positive speed) or right (negative speed).
**
** Coordinate system: X = east (+), Y = south (+).
** For direction (dx, dy), the left-strafe vector is (dy, -dx):
**   facing east  (1,0)  → left = (0,-1) = north  ✓
**   facing north (0,-1) → left = (-1,0) = west   ✓
*/
static void	strafe(t_game *game, double speed)
{
	t_player	*p;
	double		sx;
	double		sy;

	p = &game->player;
	sx = p->dir_y * speed;
	sy = -p->dir_x * speed;
	if (can_move(game, p->pos_x + sx, p->pos_y))
		p->pos_x += sx;
	if (can_move(game, p->pos_x, p->pos_y + sy))
		p->pos_y += sy;
}

/*
** Rotates the player direction and camera plane by angle (radians).
** Positive angle → clockwise on screen (right turn in Y-down coords).
*/
static void	rotate(t_game *game, double angle)
{
	t_player	*p;
	double		cos_a;
	double		sin_a;
	double		old_dx;
	double		old_px;

	p = &game->player;
	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos_a - p->dir_y * sin_a;
	p->dir_y = old_dx * sin_a + p->dir_y * cos_a;
	p->plane_x = p->plane_x * cos_a - p->plane_y * sin_a;
	p->plane_y = old_px * sin_a + p->plane_y * cos_a;
}

/*
** Reads the mouse X position each frame, computes the horizontal delta from
** the previous frame, and rotates the player accordingly.
** With MOUSE_DISABLED the cursor is hidden and its virtual position
** accumulates without bounds, giving smooth unlimited panning.
*/
static void	handle_mouse(t_game *game)
{
	int32_t	cur_x;
	int32_t	cur_y;
	int		delta;

	mlx_get_mouse_pos(game->mlx, &cur_x, &cur_y);
	delta = (int)cur_x - game->mouse_x;
	if (delta != 0)
		rotate(game, delta * MOUSE_SENS);
	game->mouse_x = (int)cur_x;
}

/*
** Polls keys each frame and updates player state:
**   W / ↑          → move forward
**   S / ↓          → move backward
**   A              → strafe left
**   D              → strafe right
**   ← / →         → rotate left / right
**   E              → interact with door (single press, not hold)
**   ESC            → close window
**   Mouse X        → rotate left / right
*/
void	handle_keys(t_game *game)
{
	mlx_t	*mlx;
	int		e_down;

	mlx = game->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		move_forward(game, MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move_forward(game, -MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		strafe(game, MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		strafe(game, -MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(game, -ROT_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(game, ROT_SPEED);
	handle_mouse(game);
	e_down = mlx_is_key_down(mlx, MLX_KEY_E);
	if (e_down && !game->key_e_prev)
		interact_door(game);
	game->key_e_prev = e_down;
	{
		int	m_down;

		m_down = mlx_is_key_down(mlx, MLX_KEY_M);
		if (m_down && !game->key_m_prev)
			game->show_minimap = !game->show_minimap;
		game->key_m_prev = m_down;
	}
}
