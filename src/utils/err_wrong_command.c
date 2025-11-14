/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_wrong_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/14 18:14:32 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	err_wrong_command(void)
{
	ft_printf("Error! Command must be like: cub3d file\n");
	return (1);
}
