/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_wrong_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 17:35:13 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	err_wrong_map(t_game *game)
{
	free(game->file);
	free(game->map);
	free(game->wall);
	ft_printf("Error! Can`t create map.\n");
	return (1);
}
