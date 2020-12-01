/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:19:07 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/28 13:46:22 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_char(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void		ft_give_env(t_data *all)
{
	int	i;

	i = 0;
	while (all->env[i])
	{
		if (ft_find_char(all->env[i]) == 1)
		{
			ft_putstr(all->env[i]);
			write(1, "\n", 1);
		}
		i++;
	}
}

void		ft_give_pwd(t_commands *cmd)
{
	char tmp[1000];

	ft_strlen(cmd->cmd);
	getcwd(tmp, 1000);
	ft_putstr(tmp);
	write(1, "\n", 1);
}
