/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 12:25:19 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

char	*ft_findchr(const char *str, int symbol)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		if (str[counter] == (char)symbol)
			return ((char *) &str[counter]);
		counter++;
	}
	if ((char)symbol == '\0')
	{
		return ((char *) &str[counter]);
	}
	return (NULL);
}
