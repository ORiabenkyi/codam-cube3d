/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 16:20:16 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	prints(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("Try print file with %d string\n", game->size_file);
	while (i < game->size_file && game->data[i])
	{
		ft_printf("%d\t!%d\t-%s", i, ft_strlen(game->data[i]), game->data[i]);
		i++;
	}
	ft_printf("\nKlaar!\n");
	return (0);
}

int	printm(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		ft_printf("%s", game->map[i]);
		i++;
	}
	return (0);
}

int	printd(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->size_file)
	{
		ft_printf("%s", game->data[i]);
		i++;
	}
	return (0);
}


int	printt(t_game *game)
{
	int	i;

	i = 0;
	if (game->wall)
	{
		ft_printf("%s", game->wall->north);
		ft_printf("%s", game->wall->south);
		ft_printf("%s", game->wall->west);
		ft_printf("%s", game->wall->east);
		i++;
	}
	return (0);
}

int	printc(t_game *game)
{
	// ft_printf("Debug mode %d\n", 3);
	if (game->floor)
		ft_printf("%s %d, %d, %d \n", "FLOOR", game->floor->red,
			game->floor->green, game->floor->blue);
	if (game->ceiling)
		ft_printf("%s %d, %d, %d \n", "CEILING", game->ceiling->red,
			game->ceiling->green, game->ceiling->blue);
	return (0);
}
