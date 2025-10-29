/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:20:06 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 11:05:11 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

size_t	ft_lenstr(const char *str)
{
	size_t	counter;

	counter = 0;
	if (str != NULL)
		while (str[counter] != '\0')
			counter++;
	return (counter);
}
