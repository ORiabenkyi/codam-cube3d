/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/22 14:33:54 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	extend_map(t_game *game)
{
	int		counter;
	int		line_counter;
	char	ch;
	int		number_player;

	counter = -1;
	number_player = -1;
	while (++counter < game->size_map)
	{
		line_counter = ft_strlen(game->map[counter]);
		while (line_counter--)
		{
			ch = game->map[counter][line_counter];
			if (is_player_chareckter(ch))
				number_player++;
			if (ch == ' ' || ch == '\t')
				game->map[counter][line_counter] = '1';
		}
	}
	return (number_player);

}

int	check_map(t_game *game)
{
	int	counter;

	if (extend_map(game))
		return (1);
	counter = -1;
	while (++counter < game->size_map)
	{
		(void)game->map[counter];
	}
	return (0);
}
