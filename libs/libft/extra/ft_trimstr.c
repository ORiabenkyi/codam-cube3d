/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 12:30:53 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

char	*ft_trimstr(char const *str1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!str1)
		return (0);
	start = 0;
	end = ft_lenstr(str1);
	if (end == 0)
		return (ft_dupstr(""));
	while (ft_findchr(set, str1[start]) && str1[start] != '\0')
		start++;
	if (start == end)
		return (ft_dupstr(""));
	while (ft_findchr(set, str1[end - 1]) && end != 0)
		end--;
	trim = ft_strsub(str1, start, end - start);
	return (trim);
}
