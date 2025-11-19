/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/15 16:13:38 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	prints(t_game *game)
{
	int	i;

	ft_printf("Debug mode 3 %d\n", game->size_file);
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