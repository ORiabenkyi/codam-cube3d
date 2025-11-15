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
	game->data = malloc(sizeof(char *) * (game->size_file + 1));
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
	t_game	*o_game;

	o_game = malloc(sizeof(t_game));
	if (!o_game)
		return (err_wrong_alocate());
	ft_memset(o_game, 0, sizeof(t_game));
	o_game->file = ft_strdup(file);
	if (!o_game->file)
		return (free(o_game), err_wrong_alocate());
	o_game->map = malloc(sizeof(char *) * 1);
	if (!o_game->map)
		return (free(o_game->file), free(o_game), err_wrong_alocate());
	o_game->data = malloc(sizeof(char *) * 1);
	if (!o_game->data)
		return (free(o_game->map), free(o_game->file),
			free(o_game), err_wrong_alocate());
	o_game->size_file = size_file(o_game->file);
	if (o_game->size_file < 7)
		return (free(o_game->map), free(o_game->file), free(o_game),
			err_wrong_in_file());
	if (read_to_memory(o_game) < 0)
		return (err_wrong_alocate());
	*game = *o_game;
	return (0);
}
