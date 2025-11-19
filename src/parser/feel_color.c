/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 17:43:47 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	int	is_only_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) || is_whitespace(str[i]))
			continue ;
		return (0);
	}
	return (1);
}

static int	add_color(t_color *color, char *str)
{
	char	**trims;
	int		i;

	i = 256;
	trims = ft_split(str, ',');
	if (!trims)
		return (1);
	if (trims[0] && is_only_number(trims[0]))
		i = ft_atoi(trims[0]);
	if (i > 255 || i < 0)
		return (clean_array(trims, 1));
	color->red = i;
	i = 256;
	if (trims[1])
		i = ft_atoi(trims[1]);
	if (i > 255 || i < 0)
		return (clean_array(trims, 1));
	color->green = i;
	i = 256;
	if (trims[2])
		i = ft_atoi(trims[2]);
	if (i > 255 || i < 0)
		return (clean_array(trims, 1));
	color->blue = i;
	return (0);
}

t_color	*create_color(t_color *color, char *str)
{
	char	*ptr;
	t_color	*new_color;

	if (color)
		return (NULL);
	new_color = malloc(sizeof(t_color));
	if (!new_color)
		return (NULL);
	ft_memset(new_color, 0, sizeof(t_color));
	ptr = str + 1;
	while (*ptr && *ptr == ' ')
		ptr++;
	if (add_color(new_color, ptr) != 0)
	{
		free(new_color);
		return (NULL);
	}
	return (new_color);
}

int	feel_color(t_game *game)
{
	int	counter;

	counter = 0;
	while (counter < game->size_file)
	{
		if (game->data[counter][0] == 'F')
		{
			game->floor = create_color(game->floor, game->data[counter]);
			if (!game->floor)
				return (1);
		}
		if (game->data[counter][0] == 'C')
		{
			game->ceiling = create_color(game->ceiling, game->data[counter]);
			if (!game->ceiling)
				return (1);
		}
		counter++;
	}
	printc(game);
	if (!game->ceiling || !game->floor)
		return (1);
	return (0);
}
