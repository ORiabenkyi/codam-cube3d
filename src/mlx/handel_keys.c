/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/12/02 13:55:43 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	handel_keys(mlx_key_data_t keydruk, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydruk.action == MLX_PRESS || keydruk.action == MLX_REPEAT)
	{
		if (keydruk.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		// else if (keydruk.key == MLX_KEY_W)
		// 	move_player_forward(game);
		// else if (keydruk.key == MLX_KEY_S)
		// 	move_player_backward(game);
		// else if (keydruk.key == MLX_KEY_A)
		// 	move_player_left(game);
		// else if (keydruk.key == MLX_KEY_D)
		// 	move_player_right(game);
		// else if (keydruk.key == MLX_KEY_LEFT)
		// 	rotate_player(game, ROTATE_LEFT);
		// else if (keydruk.key == MLX_KEY_RIGHT)
		// 	rotate_player(game, ROTATE_RIGHT);
		// else if (keydruk.key == MLX_KEY_SPACE)
		// 	handle_door_interaction(&game->map, &game->player);
	}
}
