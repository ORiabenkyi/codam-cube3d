#include "cube3d.h"

/*
** Called by MLX42 once per frame.
** Processes input first, then re-renders the scene.
*/
void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys(game);
	update_doors(game);
	render_frame(game);
	draw_minimap(game);
}
