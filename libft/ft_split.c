/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 21:37:52 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 15:16:53 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			free_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	ft_malloc_error();
}

static int		count_sym(char const *s, char c)
{
	int i;

	i = 0;
	while (*s != c && *(s++))
		i++;
	return (i);
}

static int		count_words(char const *s, char c)
{
	int		cut;

	cut = 0;
	if (*s && *s != c)
	{
		s++;
		cut++;
	}
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s != c && *s)
				cut++;
		}
		if (!(*s))
			return (cut);
		s++;
	}
	return (cut);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	if (!s || !(str = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		ft_malloc_error();
	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!(str[j] = (char*)malloc(sizeof(char) * (count_sym(s, c) + 1))))
				free_str(str);
			while (*s != c && *s)
				str[j][i++] = *s++;
			str[j++][i] = '\0';
			i = 0;
		}
	}
	str[j] = NULL;
	return (str);
}
