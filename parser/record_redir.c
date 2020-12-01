/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:16:21 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 12:17:46 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		slip_2_mas(char ***dst, char ***src)
{
	char	**a;
	char	**b;
	size_t	size;

	if (!(*src) || ft_array_size(*src) < 2)
		return ;
	size = ft_array_size(*dst) + ft_array_size(*src);
	a = (char **)ft_calloc(sizeof(char *) * size, 1);
	a[size - 1] = NULL;
	record_mas_to_mas(&a, (*dst), 0);
	record_mas_to_mas(&a, (*src) + 1, ft_array_size(*dst));
	free_msv(*dst);
	b = (char **)ft_calloc(sizeof(char *) * 2, 1);
	b[1] = NULL;
	b[0] = ft_strdup((*src)[0]);
	size = 0;
	while ((*src)[size])
	{
		free((*src)[size]);
		(*src)[size] = NULL;
		size++;
	}
	free((*src));
	(*src) = b;
	(*dst) = a;
}

void		record_arg(t_commands *pipe, t_commands *redir)
{
	if (redir->redir)
		record_arg(pipe->redir, redir->redir);
	slip_2_mas(&pipe->arg, &redir->arg);
	pipe->invalid += redir->invalid;
}

void		record_valid_next(t_commands *pipe)
{
	if (pipe->pipe)
	{
		record_valid_next(pipe->pipe);
		pipe->invalid += pipe->pipe->invalid;
	}
}

void		record_valid_line(t_commands *next)
{
	if ((next->next && next->next->cmd) ||
			(next->next && next->next->next))
	{
		record_valid_line(next->next);
		next->invalid += next->next->invalid;
	}
}

void		record_redir(t_commands *cmd, t_data *all)
{
	t_commands	*pipe;
	t_commands	*next;
	t_commands	*redir;

	next = cmd;
	while (next)
	{
		pipe = next;
		while (pipe)
		{
			give_directory(pipe, all);
			redir = pipe->redir;
			if (redir)
				record_arg(pipe, redir);
			pipe = pipe->pipe;
		}
		record_valid_next(next);
		next = next->next;
	}
	next = cmd;
	next = cmd;
	record_valid_line(next);
}
