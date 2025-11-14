/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:31 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/14 18:28:52 by oriabenk         ###   ########.fr       */
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

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/inc/libft.h"

typedef struct s_texture
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
}						t_texture;

typedef struct s_color
{
	unsigned char		red;
	unsigned char		green;
	unsigned char		blue;
}					t_color;

typedef struct s_game
{
	char				*file;
	int					size_file;
	char				**map;
	struct s_texture	*wall;
	struct s_color		*floor;
	struct s_color		*ceiling;
	mlx_t				*mlx;
	mlx_image_t			*img;
}						t_game;

int	init_game(t_game *game, int counter, char **argument);
int	is_valid_input(t_game *game, int count, char **arg);
int	feel_texture(t_game *game);
int	feel_game(t_game *game, char *file);

int	engine(t_game *game);

/*
error managment
*/

int	err_wrong_command(void);
int	err_wrong_file(void);
int	err_wrong_in_file(void);
int	err_wrong_alocate(void);
int	err_wrong_texture(t_game *game);

#endif