/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 12:31:31 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

char	*ft_dupnstr(const char *str, size_t strlen)
{
	char	*tmp;

	tmp = (char *)malloc(strlen + 1);
	if (tmp == NULL)
		return (NULL);
	ft_memcopy(tmp, str, strlen);
	tmp[strlen] = '\0';
	return (tmp);
}
