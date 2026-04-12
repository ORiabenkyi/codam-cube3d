#include "cube3d.h"
/*
** Steps along the player's direction in small increments up to INTERACT_DIST.
** Returns the first door cell found, skipping already-visited grid cells.
** Stops early if a solid wall or space is hit before finding a door.
*/
static t_door	*get_door_in_front(t_game *game)
{
	double	step;
	int		fx;
	int		fy;
	int		prev_fx;
	int		prev_fy;
	char	c;

	prev_fx = (int)game->player.pos_x;
	prev_fy = (int)game->player.pos_y;
	step = 0.1;
	while (step <= INTERACT_DIST)
	{
		fx = (int)(game->player.pos_x + game->player.dir_x * step);
		fy = (int)(game->player.pos_y + game->player.dir_y * step);
		step += 0.1;
		if (fx == prev_fx && fy == prev_fy)
			continue ;
		prev_fx = fx;
		prev_fy = fy;
		if (fy < 0 || fy >= game->map.rows || fx < 0)
			break ;
		if (fx >= (int)ft_strlen(game->map.grid[fy]))
			break ;
		c = game->map.grid[fy][fx];
		if (c == 'D' || c == 'H')
			return (find_door(&game->map, fx, fy));
		if (c == '1' || c == ' ')
			break ;
	}
	return (NULL);
}

/*
** Called on a single E key press.
** Opens a closed door in front of the player.
** Closes an open door if the player is not standing inside it.
*/
void	interact_door(t_game *game)
{
	t_door	*door;

	door = get_door_in_front(game);
	if (!door)
		return ;
	if (door->state == DOOR_CLOSED)
	{
		door->state = DOOR_OPEN;
		door->timer = 0.0;
	}
	else if (!player_in_door(game, door))
	{
		door->state = DOOR_CLOSED;
		door->timer = 0.0;
	}
}