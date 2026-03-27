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

int	init_mlx(t_game *game)
{
	(void)game;
	if (!game || !game->map)
		return (1);
	game->mlx = mlx_init(RESOLUTIONW, RESOLUTIONH, TITEL, 0);
	if (!game->mlx)
		return (error_define_mlx());
	mlx_cursor_hook(game->mlx, &handel_mouse, &game);
	mlx_key_hook(game->mlx, &handel_keys, &game);
	mlx_close_hook(game->mlx, &handle_window_close, &game);
	mlx_loop_hook(game->mlx, &rebuild_window, &game);
	mlx_loop(game->mlx);

	return (0);
}
