/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/15 15:14:18 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

int	ft_clean_array(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (1);
	while (array[len])
	{
		free(array[len]);
		array[len] = NULL;
		len++;
	}
	free(array);
	return (0);
}
