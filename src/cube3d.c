/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:57:00 by oriabenk          #+#    #+#             */
/*   Updated: 2025/12/02 13:21:20 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

int	main(int count, char *arg[])
{
	t_game		game;

	if (init_game(&game, count, arg) != 0)
	{
		ft_printf("Wrong init game.\n");
		free_all(&game);
		return (1);
	}
	if (init_mlx(&game) != 0)
	{
		ft_printf("Wrong init mlx.\n");
		free_all(&game);
		return (1);
	}
	free_all(&game);
	return (0);
}
