/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:23:21 by oriabenk          #+#    #+#             */
/*   Updated: 2025/05/11 12:32:45 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

static size_t	word_counter(char *str, char *delimiter)
{
	size_t	count;
	char	*trimmed_str;
	int		i;

	trimmed_str = ft_trimstr(str, delimiter);
	if (trimmed_str == NULL)
		return (-1);
	count = 0;
	i = 0;
	if (ft_findchr(delimiter, trimmed_str[i]) == NULL)
		count++;
	while (trimmed_str[i])
	{
		if (ft_findchr(delimiter, trimmed_str[i]) != NULL)
			count++;
		i++;
	}
	free(trimmed_str);
	return (count);
}

static void	*free_words(char **array, size_t words_in_array)
{
	while (words_in_array--)
		free(array[words_in_array]);
	free(array);
	return (NULL);
}

char	**ft_split_set(char const *str, char *delimiter)
{
	size_t	word_count;
	char	**array;
	size_t	word_index;
	char	*start_word;

	word_count = word_counter((char *)str, delimiter);
	array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	word_index = 0;
	while (word_index < word_count && *str)
	{
		while (*str && ft_findchr(delimiter, *str) != NULL)
			str++;
		start_word = (char *)str;
		while (*str != '\0' && ft_findchr(delimiter, *str) == NULL)
			str++;
		array[word_index] = ft_dupnstr(start_word, str - start_word);
		if (!array[word_index])
			return (free_words(array, word_index));
		word_index++;
	}
	array[word_index] = NULL;
	return (array);
}
