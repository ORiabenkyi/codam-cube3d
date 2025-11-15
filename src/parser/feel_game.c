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

static int	size_file(char *line)
{
	int	i;
	int fd;
	char	*str;

	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		i++;
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}
static int	read_to_memory(t_game *game)
{
	int	fd;
	int i;
	char	*line;

	game->size_file = size_file(game->file);
	if (game->size_file < 0)
		return (perror("Error\nFile open error"), 1);
	fd = open(game->file, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFile open error"), 1);
	game->data = malloc(sizeof(char *) * (game->size_file + 1));
	if (!game->data)
		return (perror("Error\nMemory allocation error"), 1);
	i = 0;
	while (i < game->size_file)
	{
		line = get_next_line(fd);
		if (!line)
			return (perror("Error\nFile read error"), 1);
		game->data[i] = line;
		i++;
	}
	game->data[i] = NULL;
	close(fd);		
	return (0);
}

int	feel_game(t_game *game, char *file)
{

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
