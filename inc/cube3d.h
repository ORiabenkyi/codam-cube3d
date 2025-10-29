/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:31 by oriabenk          #+#    #+#             */
/*   Updated: 2025/10/29 15:31:18 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "./libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/inc/libft.h"

typedef struct s_texture
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	mlx_texture_t		*mnorth;
	mlx_texture_t		*msouth;
	mlx_texture_t		*meast;
	mlx_texture_t		*mwest;
}						t_texture;

typedef struct s_game
{
	char				**file;
	char				**map;
}						t_game;


int	init_game(t_game *game, int counter, char **argument);

#endif