/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/15 13:19:24 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

char	*ft_dupstr(const char *income_str)
{
	int		length;
	char	*tmp;
	char	*tmp2;

	if (income_str == NULL)
		return (NULL);
	length = ft_lenstr(income_str);
	tmp = (char *)malloc((length + 1) * sizeof(*tmp));
	if (tmp == NULL)
		return (NULL);
	tmp2 = tmp;
	while (income_str && *income_str)
	{
		*tmp++ = *income_str++;
	}
	*tmp = '\0';
	return (tmp2);
}
