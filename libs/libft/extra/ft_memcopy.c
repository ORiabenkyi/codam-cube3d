/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 12:24:09 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

void	*ft_memcopy(void *dest, const void *src, size_t n)
{
	size_t			counter;
	char			*destination;
	const char		*source;

	counter = 0;
	destination = dest;
	source = src;
	if (!dest && !src)
		return (NULL);
	while (counter < n)
	{
		destination[counter] = source[counter];
		counter++;
	}
	return (dest);
}
