/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/14 18:35:29 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

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
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		game->size_file++;
	}
	close(fd);
	return (0);
}
