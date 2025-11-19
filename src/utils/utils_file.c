/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:09:57 by oriabenk          #+#    #+#             */
/*   Updated: 2025/11/19 16:46:13 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	is_whitespace(int symbol)
{
	if (symbol == ' ' || symbol == '\t' || symbol == '\v')
		return (1);
	else if (symbol == '\n' || symbol == '\r' || symbol == '\f')
	{
		return (1);
	}
	return (0);
}

int	clean_array(char **array, int endig)
{
	int	len;

	len = 0;
	if (!array)
		return (endig);
	while (array[len])
	{
		free(array[len]);
		array[len] = NULL;
		len++;
	}
	free(array);
	return (endig);
}

int	is_valid_file(char *file)
{
	int			fd;
	const char	*extension;

	fd = 0;
	extension = ft_strchr(file, '.');
	if (!extension)
		return (1);
	if (ft_strncmp(extension, ".cub", 4) != 0)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}
