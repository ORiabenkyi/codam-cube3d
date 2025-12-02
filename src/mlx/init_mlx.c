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

static int 

int	init_mlx(t_game *game)
{
	(void)game;
	if (!game || !map)
		return (1);
	game->mlx = mlx_init(RESOLUTIONW, RESOLUTIONH, TITEL, 0);
	if (!game->mlx)
		return (error_define_mlx());
	return (0);
}
