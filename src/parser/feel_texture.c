/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 16:23:30 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	char	*add_textur(char *str, char *ptr)
{
	if (str)
	{
		free(str);
		return (NULL);
	}
	return (ft_strdup(ptr));
}

static	int	add_textur1(t_texture *muur, char *str)
{
	char	*ptr;

	ptr = str + 2;
	while (*ptr && *ptr == ' ')
		ptr++;
	if (str[0] == 'N')
	{
		muur->north = add_textur(muur->north, ptr);
		if (!muur->north)
			return (1);
	}
	if (str[0] == 'S')
	{
		muur->south = add_textur(muur->south, ptr);
		if (!muur->south)
			return (1);
	}
	return (0);
}

static	int	add_textur2(t_texture *muur, char *str)
{
	char	*ptr;

	ptr = str + 2;
	while (*ptr && *ptr == ' ')
		ptr++;
	if (str[0] == 'W')
	{
		muur->west = add_textur(muur->west, ptr);
		if (!muur->west)
			return (1);
	}
	if (str[0] == 'E')
	{
		muur->east = add_textur(muur->east, ptr);
		if (!muur->east)
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
	ft_memset(game->wall, 0, sizeof(t_texture));
	while (counter < game->size_file)
	{
		if (game->data[counter][0] == 'N' || game->data[counter][0] == 'S')
			if (add_textur1(game->wall, game->data[counter]) != 0)
				return (1);
		if (game->data[counter][0] == 'W' || game->data[counter][0] == 'E')
			if (add_textur2(game->wall, game->data[counter]) != 0)
				return (1);
		counter++;
	}
	printt(game);
	return (0);
}
