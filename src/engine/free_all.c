/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:08 by oriabenk          #+#    #+#             */
/*   Updated: 2025/12/02 13:30:26 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	free_all( t_game *game)
{
	
	if (game->file)
		free(game->file);
	if (game->data)
		clean_array(game->data, game->size_file);
	if (game->map)
		clean_array(game->map, game->size_map);
	if (game->wall)
	{
		free_texture(game->wall);
		free(game->wall);
	}
	if (game->floor)
		free(game->floor);
	if (game->ceiling)
		free(game->ceiling);
	if (game->mlx)
		mlx_terminate(game->mlx);
	return (0);
}
