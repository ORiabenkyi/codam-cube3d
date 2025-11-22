/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/22 14:28:58 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	is_service_line(char *str)
{
	if (str[0] == '\n')
		return (1);
	if (ft_strlen(str) < 4)
		return (0);
	if (str[0] == 'N' && str[1] == 'O' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'S' && str[1] == 'O' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'W' && str[1] == 'E' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'E' && str[1] == 'S' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'F' && (str[1] == ' ' || str[1] == '\t'))
		return (1);
	if (str[0] == 'C' && (str[1] == ' ' || str[1] == '\t'))
		return (1);
	return (0);
}

static	int	is_map_chareckter(int symbol)
{
	if (symbol == '1' || symbol == '0')
		return (1);
	return (0);
}

static	int	checks_map(t_game *game)
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

static	char	*strdupn(const char *income_str, int length)
{
	int		counter;
	char	*outcome_str;
	int		len;

	counter = 0;
	outcome_str = (char *)malloc((length) * sizeof(char));
	if (!outcome_str)
		return (NULL);
	len = ft_strlen(income_str);
	while (counter < (length - 1))
	{
		if (counter >= (len - 1))
			outcome_str[counter] = '\0';
		else
			outcome_str[counter] = income_str[counter];
		counter++;
	}
	outcome_str[counter] = '\0';
	return (outcome_str);
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
		game->map[++counter] = strdupn(game->data[i], game->size_line);
	}
	printm(game);
	return (checks_map(game));
}
