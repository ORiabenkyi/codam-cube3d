/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_wrong_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 14:43:16 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	free_texture(t_texture *texture)
{
	if (texture->north)
		free(texture->north);
	if (texture->south)
		free(texture->south);
	if (texture->west)
		free(texture->west);
	if (texture->east)
		free(texture->east);
}

int	err_wrong_color(t_game *game)
{
	free(game->file);
	free(game->map);
	free_texture(game->wall);
	free(game->wall);
	free(game->ceiling);
	free(game->floor);
	ft_printf("Error! Can`t create color.\n");
	return (1);
}
