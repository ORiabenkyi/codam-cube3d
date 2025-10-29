/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 13:11:49 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*s;
	int		i;
	int		j;

	if (!str1 && !str2)
		return (NULL);
	i = -1;
	j = -1;
	s = (char *)malloc((ft_lenstr(str1) + ft_lenstr(str2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (++i < (int)ft_lenstr(str1))
		s[i] = str1[i];
	while (++j < (int)ft_lenstr(str2))
		s[i + j] = str2[j];
	s[i + j] = '\0';
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	str1 = NULL;
	str2 = NULL;
	return (s);
}
