/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:47:44 by skarry            #+#    #+#             */
/*   Updated: 2020/10/29 18:15:13 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		if_backslash(char **line, int *i, char **w, int *er)
{
	if (!((*line)[*i + 1]))
	{
		(*i)++;
		*er = 1;
		return (1);
	}
	*w = re_malloc((*line)[*i + 1], *w);
	*i += 2;
	return (0);
}

int		if_dollar(char *line, t_data *all, char **w)
{
	int		i;
	int		j;
	char	*var;
	int		num_var;

	i = 1;
	while (line[i] == 95 || (line[i] > 64 && line[i] < 91) ||
						(line[i] > 96 && line[i] < 123))
		i++;
	if (i == 1)
	{
		*w = re_malloc('$', *w);
		return (i);
	}
	var = ft_strtosup(line + 1, i - 1);
	if ((num_var = give_variable(all->env, var)) > -1)
	{
		j = ft_strlen(var) + 1;
		j--;
		while (all->env[num_var][++j])
			*w = re_malloc(all->env[num_var][j], *w);
	}
	free(var);
	return (i);
}

int		if_double_quotes(char *line, t_data *all, char **w, int *er)
{
	int		i;

	i = 1;
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '\\')
		{
			if (if_backslash(&line, &i, w, er))
				return (1);
		}
		else if (line[i] == '$')
			i += if_dollar(line + i, all, w);
		else
			*w = re_malloc(line[i++], *w);
	}
	if (line[i])
		i++;
	else
		*er = 1;
	if (!*w)
		if (line[i] == ' ')
			*w = ft_strdup("");
	return (i);
}

int		if_single_quotes(char **line, int i, char **w, int *er)
{
	while ((*line)[i++] && (*line)[i] != '\'')
		*w = re_malloc((*line)[i], *w);
	if ((*line)[i])
		i++;
	else
		*er = 1;
	if (!*w)
		if ((*line)[i] == ' ')
			*w = ft_strdup("");
	return (i);
}

char	*get_word(char **line, int *er, t_data *all)
{
	char	*w;
	int		i;

	w = NULL;
	i = skip_space((*line));
	while (((*line)[i] != ' ' && (*line)[i]) || (!w && (*line)[i]))
	{
		if (!w)
			i += skip_space((*line + i));
		if (*er == 1)
			break ;
		else
			i = if_basesim((*line), i, all, &w);
	}
	*line = *line + i;
	return (w);
}
