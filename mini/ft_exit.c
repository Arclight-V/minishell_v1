/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:50:42 by skarry            #+#    #+#             */
/*   Updated: 2020/10/30 13:49:31 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(t_commands *cmd, t_data *all, t_commands *pip)
{
	if (!pip->pipe)
	{
		write(1, "exit\n", 5);
		if (cmd->arg[1])
		{
			if (ft_check_str(cmd->arg[1]) == 0)
			{
				ft_putstr("minishell: exit: ");
				ft_putstr(cmd->arg[1]);
				ft_putstr(": numeric argument required\n");
				free(all->error);
				all->error = ft_strdup("255");
			}
			else if (cmd->arg[2])
			{
				ft_putstr("minishell: exit: too many arguments\n");
				free(all->error);
				all->error = ft_strdup("1");
				return ;
			}
			else
				exit(ft_atoi(cmd->arg[1]));
		}
		exit(ft_atoi(all->error));
	}
}

void		ft_give_tilda(t_commands *cmd, t_data *all)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strdup(all->home_dir + 5);
	tmp2 = ft_strjoin(tmp, cmd->arg[1] + 1);
	free(tmp);
	free(cmd->arg[1]);
	cmd->arg[1] = tmp2;
}
