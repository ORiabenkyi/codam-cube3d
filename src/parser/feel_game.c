/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/15 16:47:40 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	size_file(char *line)
{
	int		i;
	int		fd;
	char	*str;

	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (ft_strlen(str) > 1)
			i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}

static int	read_to_memory(t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(game->file, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFile open error"), 1);
	game->data = (char **)malloc(sizeof(char *) * (game->size_file + 1));
	if (!game->data)
		return (perror("Error\nMemory allocation error"), 1);
	i = 0;
	while (i < game->size_file)
	{
		line = get_next_line(fd);
		if (!line)
			return (perror("Error\nFile read error"), 1);
		if (ft_strlen(line) <= 1)
		{
			free(line);
			continue ;
		}
		game->data[i++] = line;
	}
	game->data[i] = NULL;
	return (close(fd));
}

int	feel_game(t_game *game, char *file)
{
	game->file = ft_strdup(file);
	if (!game->file)
		return (err_wrong_alocate());
	game->map = (char **)malloc(sizeof(char *) * 1);
	if (!game->map)
		return (free(game->file), err_wrong_alocate());
	// game->data = (char **)malloc(sizeof(char *) * 1);
	// if (!game->data)
	// 	return (free(game->map), free(game->file),
	// 		err_wrong_alocate());
	game->size_file = size_file(game->file);
	if (game->size_file < 7)
		return (free(game->map), free(game->file),
			free(game->data), err_wrong_in_file());
	if (read_to_memory(game) < 0)
		return (err_wrong_alocate());
	return (0);
}
