/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/15 12:14:46 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	read_to_memory(t_game *game)
{
	(void)game;
	return (0);
}

int	feel_game(t_game *game, char *file)
{
	int			fd;
	char		*line;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	ft_memset(game, 0, sizeof(t_game));
	game->file = ft_strdup(file);
	if (!game->file)
		return (free(game), 1);
	game->map = malloc(sizeof(char *) * 1);
	if (!game->map)
		return (free(game->file), free(game), 1);
	game->data = malloc(sizeof(char *) * 1);
	if (!game->data)
		return (free(game->map), free(game->file), free(game), 1);
	if (read_to_memory(game))
		return (1);
	return (0);
}
