/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:57:00 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 15:25:35 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

int	main(int count, char *arg[])
{
	t_game		game;

	if (init_game(&game, count, arg) != 0)
	{
		ft_printf("Wrong init game.\n");
		return (1);
	}
	return (0);
}
