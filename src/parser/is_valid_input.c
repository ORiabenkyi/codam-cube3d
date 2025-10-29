/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:10:01 by oriabenk          #+#    #+#             */
/*   Updated: 2025/10/29 17:50:50 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_valid_file(char *file);
int	is_valid_in_file(char *file);

int	is_valid_input(int count, char **arg)
{
	if (count != 2)
		return (err_wrong_command());
	if (is_valid_file(arg[1]) != 0)
		return (err_wrong_file());
	if (is_valid_in_file(arg[1]) != 0)
		return (err_wrong_in_file());
	return (0);
}

int	is_valid_file(char *file)
{
	int			fd;
	const char	*extension;

	fd = 0;
	extension = ft_strchr(file, '.');
	if (!extension)
		return (1);
	if (ft_strcmp(extension, ".cub") != 0)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

