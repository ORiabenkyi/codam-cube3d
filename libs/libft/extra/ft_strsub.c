/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 12:29:40 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	counter;
	size_t	length;

	if (!str)
		return (0);
	if (ft_lenstr(str) < (size_t)start)
		return (ft_dupstr(""));
	length = ft_lenstr(str) - start;
	if (length < len)
		tmp = (char *)malloc((length + 1) * sizeof(char));
	else
		tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	counter = 0;
	while (counter < len && str[start + counter])
	{
		tmp[counter] = (char)str[counter + start];
		counter++;
	}
	tmp[counter] = '\0';
	return (tmp);
}
