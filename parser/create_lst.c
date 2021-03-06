/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatashi <anatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:31:44 by skarry            #+#    #+#             */
/*   Updated: 2020/12/01 22:55:43 by anatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				check_env(char	**envp, char *var, int size)
{
	int			i;
	int			j;
	int			recover_size;

	recover_size = size;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		if (envp[i][j] == var[j])
		{
			size = recover_size;
			while (envp[i][j] == var[j] && size)
			{	
				if ((envp[i][j + 1] == '=' || envp[i][j + 1] == '\0') && size == 1)
					return (i);
				j++;
				size--;
			}
		}
	}
	return (0);
}

char		*ft_strjoin_gnl(char **s1, char *s2)
{
	char	*new_str;
	size_t	j;
	size_t	i;

	if (!*s1 || !s2)
		return (NULL);
	i = 0;
	j = ft_strlen(*s1) + ft_strlen(s2) + 1;
	if (!(new_str = (char *)malloc(j * sizeof(char))))
		return (NULL);
	j = 0;
	while ((*s1)[i])
		new_str[j++] = (*s1)[i++];
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	free(*s1);
	return (new_str);
}

/*
** p 	- a pointer to the CHAR_DOLLAR
** rem	- the remainder of the string after $ content
*/
void			_if_type_dollar(t_data *data, char **content, char *rem)
{
	char		*p;
	int			i;
	int			num_env;

	i = 0;
	p = rem ? ft_strchr(rem, '$') : ft_strchr(*content, '$');
	if (p)
	{
		p++;
		i = (p[i] == '_' || ft_isalpha(p[i])) ? 1 : 0;
		if (i)
		{
			while (p[i] == '_' || ft_isalnum(p[i]))
				i++;
			if ((num_env = check_env(data->env, p, i)))
			{
				p--;
				*p = '\0';
				rem = ft_strdup(p + i + 1);
				*content = ft_strjoin_gnl(content, data->env[num_env] + i + 1);
				if (rem != '\0')
					_if_type_dollar(data, content, rem);
			}
			else
			{
				// ft_free_tmp(*content);
				free (*content);
				content = NULL;
				*content = ft_strdup("");
			}
			

		}
	}
}

void 		_strip_quotes(char *content, size_t n, int j)
{
	size_t 	i;
	char	lastquote;
	char	c;

	i = -1;
	lastquote = 0;
	while (++i < n)
	{
		c = content[i];
		if ((c == '\'' || c == '\"') && lastquote == 0)
			lastquote = c;
		else if (c == lastquote)
			lastquote = 0;
		else
			content[j++] = c;
	}
	content[j] = 0;
}

size_t		skip_space(char *s)
{
	size_t		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	return (i);
}

void		give_type_direct(char *line, t_commands *s_point, size_t end_cmd)
{
	if (line[end_cmd] == '<')
		s_point->type_redir = 1;
	if (line[end_cmd] == '>')
		s_point->type_redir = 2;
	if (line[end_cmd] == '>' && line[end_cmd + 1] == '>')
		s_point->type_redir = 3;
}

void		write_data(t_commands *s_point, size_t *point,
										char *line, t_data *all)
{
	char	*line2;
	size_t	end_cmd;
	int		dquote;

	end_cmd = 0;
	dquote = 0;
	*point += skip_space(line + *point);
	line2 = (char *)malloc(sizeof(char) * (ft_strlen(line) - end_cmd - *point));
	end_cmd += *point;
	find_end_cmd(line + *point, &end_cmd, &line2, &dquote);
	if (dquote)
		_if_type_dollar(all, &line2, NULL);
	_strip_quotes(line2, ft_strlen(line2), 0);
	s_point->arg = line_to_mas(line2, &s_point->invalid, all);
	free(line2);
	if (!s_point->arg[0])
		s_point->invalid = 1;
	else
		s_point->cmd = ft_strdup(s_point->arg[0]);
	*point += skip_space(line + *point);
	give_type_direct(line, s_point, end_cmd);
	*point = end_cmd + 1;
	if (s_point->type_redir == 3)
		(*point)++;
}

t_commands	*create_lst(char *line, t_data *all)
{
	size_t		point;
	t_commands	*cmd;

	cmd = (t_commands *)ft_calloc(sizeof(t_commands), 1);
	point = 0;
	if (*line)
	{
		write_data(cmd, &point, line, all);
		add_lst(line, cmd, point, all);
		record_redir(cmd, all);
	}
	return (cmd);
}
