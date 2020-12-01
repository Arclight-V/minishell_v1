/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:51:37 by skarry            #+#    #+#             */
/*   Updated: 2020/10/27 13:52:00 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_commands *cmd)
{
	if (cmd)
	{
		if (cmd->redir)
			free_cmd(cmd->redir);
		if (cmd->pipe)
			free_cmd(cmd->pipe);
		if (cmd->next)
			free_cmd(cmd->next);
		if (cmd->arg)
			free_msv(cmd->arg);
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->cmd_dir)
			free(cmd->cmd_dir);
		free(cmd);
	}
}
