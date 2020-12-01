/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:09:28 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/29 18:08:56 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		ft_printf_ec(t_data *all, t_commands *cmd, int i)
{
	while (cmd->arg[i])
	{
		if (ft_compare_str(cmd->arg[i], "$?") == 1)
		{
			ft_putstr(all->error);
			i++;
		}
		else
			ft_putstr(cmd->arg[i++]);
		if (cmd->arg[i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	free(all->error);
	all->error = ft_strdup("0");
	g_status51 = 0;
}

static void		ft_print(t_data *all, t_commands *cmd, int i)
{
	i++;
	while (cmd->arg[i])
	{
		if (ft_compare_str(cmd->arg[i], "$?") == 1)
		{
			ft_putstr(all->error);
			i++;
		}
		else
			ft_putstr(cmd->arg[i++]);
		if (cmd->arg[i])
			write(1, " ", 1);
	}
	free(all->error);
	all->error = ft_strdup("0");
	g_status51 = 0;
}

int				ft_give_echo(t_data *all, t_commands *cmd)
{
	int	i;

	i = 1;
	if (g_status51 == 1)
	{
		free(all->error);
		all->error = ft_strdup("1");
	}
	if (cmd->arg[i] != NULL)
	{
		if (ft_compare_str(cmd->arg[i], "-n") == 1)
		{
			ft_print(all, cmd, i);
			return (0);
		}
		else if (ft_compare_str(cmd->arg[i], "-n") != 1)
		{
			ft_printf_ec(all, cmd, i);
			return (0);
		}
	}
	write(1, "\n", 1);
	free(all->error);
	all->error = ft_strdup("0");
	return (0);
}
