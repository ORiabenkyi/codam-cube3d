/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 16:24:45 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	is_valid_input(t_game *game, int count, char **arg)
{
	if (count != 2)
		return (err_wrong_command());
	if (is_valid_file(arg[1]) != 0)
		return (err_wrong_file());
	if (feel_game(game, arg[1]) != 0)
		return (1);
	if (feel_texture(game) != 0)
		return (err_wrong_texture(game));
	if (feel_color(game) != 0)
		return (err_wrong_color(game));
	if (feel_map(game) != 0)
		return (err_wrong_map(game));
	return (0);
}
