/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/14 18:23:23 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	feel_texture(t_game *game)
{
	int	fd;
	int	counter;

	counter = 0;
	game->wall = malloc(sizeof(t_texture));
	if (!game->wall)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	while (1)
	{
		counter++;
		break ;
	}
	close(fd);
	return (0);
}
