/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feel_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 18:13:19 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static	char	*add_textur(char *str, char *ptr)
{
	int		i;
	char	*ret_str;

	if (str)
	{
		free(str);
		return (NULL);
	}
	ret_str = ft_strdup(ptr);
	i = 0;
	while (ret_str[i] && ret_str[i] != '\n')
		i++;
	ret_str[i] = '\0';
	return (ret_str);
}

static	int	add_textur1(t_texture *muur, char *str)
{
	char	*ptr;
	int		fd;

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
	ft_printf("file =%s line\n", ptr);
	fd = open(ptr, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

static	int	add_textur2(t_texture *muur, char *str)
{
	char	*ptr;
	int		fd;

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
	fd = open(ptr, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
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
