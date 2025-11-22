/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/22 11:16:45 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*
typedef struct s_game
{
	char				*file;
	char				**data;
	int					size_file;
	int					size_map;
	size_t				size_line;
	char				**map;
	struct s_texture	*wall;
	struct s_color		*floor;
	struct s_color		*ceiling;
	mlx_t				*mlx;
	mlx_image_t			*img;
}						t_game;
*/

static void	free_texture(t_texture *texture)
{
	if (texture->north)
		free(texture->north);
	if (texture->south)
		free(texture->south);
	if (texture->west)
		free(texture->west);
	if (texture->east)
		free(texture->east);
}

int	free_game(t_game *game)
{
	if (!game)
		return (0);
	if (game->file)
		free(game->file);
	if (game->data)
		clean_array(game->data, game->size_file);
	if (game->map)
		clean_array(game->map, game->size_map);
	if (game->wall)
	{
		free_texture(game->wall);
		free(game->wall);
	}
	if (game->floor)
		free(game->floor);
	if (game->ceiling)
		free(game->ceiling);
	return (0);
}
