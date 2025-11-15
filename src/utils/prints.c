/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_wrong_alocate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/14 18:14:29 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	prints(t_game *game)
{
	int i;

	i = 0;
	while (i < game->size_file)
	{
		ft_printf("%s", game->data[i]);
		i++;
	}
	return (0);
}

int	printm(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i])
	{	
		ft_printf("%s", game->map[i]);
		i++;
	}
	return (0);
}