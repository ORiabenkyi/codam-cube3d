#include "cube3d.h"

/*
** Returns 1 if any corner of the player's bounding box overlaps the door cell.
** Uses PLAYER_MARGIN so that partial entry is also detected.
*/
int	player_in_door(t_game *game, t_door *door)
{
	double	px;
	double	py;

	px = game->player.pos_x;
	py = game->player.pos_y;
	return (
		((int)(px - PLAYER_MARGIN) == door->x
			&& (int)(py - PLAYER_MARGIN) == door->y)
		|| ((int)(px + PLAYER_MARGIN) == door->x
			&& (int)(py - PLAYER_MARGIN) == door->y)
		|| ((int)(px - PLAYER_MARGIN) == door->x
			&& (int)(py + PLAYER_MARGIN) == door->y)
		|| ((int)(px + PLAYER_MARGIN) == door->x
			&& (int)(py + PLAYER_MARGIN) == door->y));
}
