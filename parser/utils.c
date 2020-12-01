/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:07:41 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 19:55:55 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			give_variable(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_find_equally(env[i], var) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	if_dubquot(char *s, size_t *i)
{
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '\\')
			(*i)++;
		if (s[*i])
			(*i)++;
	}
	if (!s[*i])
		return (*i);
	return (0);
}

size_t		find_end_cmd(char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '|' && s[i] != ';' && s[i] != '<' && s[i] != '>' && s[i])
	{
		if (s[i] == '\\')
			i++;
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i])
				return (i);
		}
		if (s[i] == '\"')
			if (if_dubquot(s, &i))
				return (i);
		if (s[i])
			i++;
	}
	return (i);
}

void		record_mas_to_mas(char ***m1, char **m2, int start)
{
	int		i;
	int		j;

	i = 0;
	while (m2[i])
	{
		(*m1)[start] = (char *)ft_calloc(ft_strlen(m2[i]) + 1, 1);
		j = 0;
		while (m2[i][j])
		{
			(*m1)[start][j] = m2[i][j];
			j++;
		}
		(*m1)[start][j] = '\0';
		start++;
		i++;
	}
}

char		*re_malloc(char c, char *w)
{
	char	*v;
	int		i;

	if (!w)
	{
		v = (char *)ft_calloc(2, 1);
		v[0] = c;
		v[1] = '\0';
		return (v);
	}
	v = (char *)ft_calloc(ft_strlen(w) + 2, 1);
	i = -1;
	while (w[++i])
		v[i] = w[i];
	v[i++] = c;
	free(w);
	return (v);
}
