/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/15 17:53:00 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	int	add_textur(t_texture *muur, char *str)
{
	char	*ptr;

	ptr = str + 2;
	while (*ptr && *ptr == ' ')
		*ptr++;
	if (str[0] == 'N')
	{
		if (!muur->north)
			muur->north = ft_strdup(ptr);
		else
			return (1);
	}
	if (str[0] == 'S')
	{
		if (!muur->south)
			muur->south = ft_strdup(ptr);
		else
			return (1);
	}
	if (str[0] == 'W')
	{
		if (!muur->west)
			muur->west = ft_strdup(ptr);
		else
			return (1);
	}
	if (str[0] == 'E')
	{
		if (!muur->east)
			muur->east = ft_strdup(ptr);
		else
			return (1);
	}
	return (0);
}

int	feel_texture(t_game *game)
{
	int	counter;

	counter = 0;
	game->wall = malloc(sizeof(t_texture));
	if (!game->wall)
		return (1);
	while (counter < game->size_file)
	{
		if (game->data[counter][0] == 'N' || game->data[counter][0] == 'S' ||
			game->data[counter][0] == 'W' || game->data[counter][0] == 'E')
			if (add_textur(game->wall, game->data[counter]) != 0)
				return (1);
		counter++;
	}
	return (0);
}
