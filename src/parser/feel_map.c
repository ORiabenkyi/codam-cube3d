/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 17:04:05 by oriabenk         ###   ########.fr       */
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

static	int	is_map_chareckter(int symbol)
{
	if (symbol == '1' || symbol == '0')
		return (1);
	return (0);
}

static	int	is_player_chareckter(int symbol)
{
	if (symbol == 'S' || symbol == 'N' || symbol == 'W' || symbol == 'E')
		return (1);
	return (0);
}

static	int	check_map(t_game *game)
{
	int	i;
	int	len;

	i = -1;
	while (game->map[++i])
	{
		len = ft_strlen(game->map[i]);
		while (len > 0)
		{
			if (is_whitespace(game->map[i][len - 1]) ||
				is_map_chareckter(game->map[i][len - 1])
				|| is_player_chareckter(game->map[i][len - 1]))
				len--;
			else
				return (1);
		}
	}
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
	game->map = (char **)ft_calloc(1, sizeof(char *) * (game->size_map + 1));
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
	return (check_map(game));
}
