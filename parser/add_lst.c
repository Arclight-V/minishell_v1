/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:38:41 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 11:46:14 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*create_one_lst(t_commands *lst, int t,
							t_commands **redir, t_commands **pipe)
{
	t_commands	*new;

	new = (t_commands *)ft_calloc(sizeof(t_commands), 1);
	if (t == 1)
		lst->redir = new;
	if (t == 2)
	{
		lst->pipe = new;
		(*pipe) = new;
	}
	if (t == 3)
		lst->next = new;
	*redir = new;
	return (new);
}

void		add_lst(char *line, t_commands *cmd, size_t point, t_data *all)
{
	t_commands	*pipe;
	t_commands	*next;
	t_commands	*redir;
	t_commands	*new;

	pipe = cmd;
	next = cmd;
	redir = cmd;
	new = cmd;
	while (new)
	{
		new = NULL;
		if (line[point - 1] == '>' || line[point - 1] == '<')
			new = create_one_lst(redir, 1, &redir, &pipe);
		if (line[point - 1] == '|')
			new = create_one_lst(pipe, 2, &redir, &pipe);
		if (line[point - 1] == ';')
		{
			new = create_one_lst(next, 3, &redir, &pipe);
			next = new;
			pipe = new;
		}
		if (new)
			write_data(new, &point, line, all);
	}
}
