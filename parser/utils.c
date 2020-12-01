/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatashi <anatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:07:41 by skarry            #+#    #+#             */
/*   Updated: 2020/12/01 22:52:44 by anatashi         ###   ########.fr       */
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


void		find_end_cmd(char *s, size_t *i, char **line2, int *dquote)
{
	size_t	j;

	j = 0;
	while (s[*i] != '|' && s[*i] != ';' && s[*i] != '<' && s[*i] != '>' && s[*i])
	{
		*line2[j++] = s[(*i)++];
		if (s[*i] == '\"')
			(*dquote) = 1;
	}
	*line2[j + 1] = '\0';
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
