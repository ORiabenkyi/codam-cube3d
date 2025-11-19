/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 16:12:56 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	is_service_line(char *str)
{
	if (str[0] == 'N' || str[0] == 'S' || str[0] == 'W' || str[0] == 'E'
		|| str[0] == 'F' || str[0] == 'C' || str[0] == '\n')
		return (1);
	return (0);
}

int	feel_map(t_game *game)
{
	int	counter;
	int	i;

	counter = -1;
	while (++counter < game->size_file)
	{
		if (is_service_line(game->data[counter]) == 1)
			continue ;
		if (game->size_line < ft_strlen(game->data[counter]))
			game->size_line = ft_strlen(game->data[counter]);
		game->size_map++;
	}
	game->map = (char **)malloc(sizeof(char *) * (game->size_map + 1));
	if (!game->map)
		return (perror("Error\nMemory allocation error"), 1);
	counter = -1;
	i = -1;
	while (++i < game->size_file)
	{
		if (is_service_line(game->data[i]) == 1)
			continue ;
		game->map[++counter] = ft_strdup(game->data[i]);
	}
	game->map[counter] = NULL;
	printm(game);
	return (0);
}
