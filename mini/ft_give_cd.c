/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:41:07 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/30 13:43:52 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		ft_er_cd(t_data *all, char *tmp)
{
	if (chdir(tmp) == -1)
	{
		free(all->error);
		all->error = ft_strdup("1");
		ft_putstr("minishell: cd: ");
		ft_putstr(tmp);
		ft_putstr(": No such file or directory\n");
	}
}

void			ft_give_exportss(t_commands *cmd, t_data *all, int i)
{
	int count;
	int len;

	count = ft_strlen_msv(cmd->arg);
	len = 1;
	while (len != count)
	{
		all->env[i] = NULL;
		if (ft_str_check_exp(all, all->env, cmd->arg[len]) != 1)
		{
			if (ft_str_check_exp(all, all->env, cmd->arg[len]) == 2)
			{
				i--;
				free(all->env[i]);
				all->env[i] = NULL;
			}
			all->env[i] = ft_strdup(cmd->arg[len]);
			i++;
		}
		len++;
	}
	all->env[i] = NULL;
}

static int		ft_env_update(t_data *all, char *old_pwd)
{
	char	tmp[1000];

	if (all->env_old_dir_i == -1 || all->env_dir_i == -1)
		return (0);
	free(all->env[all->env_old_dir_i]);
	all->env[all->env_old_dir_i] = ft_strjoin("OLDPWD=", old_pwd);
	getcwd(tmp, 1000);
	free(all->env[all->env_dir_i]);
	all->env[all->env_dir_i] = ft_strjoin("PWD=", tmp);
	return (0);
}

static char		*ft_env_replace_home(t_commands *cmd, t_data *all)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 5;
	if (all->env_home_dir == -1 && cmd->arg[1] == NULL)
	{
		free(all->error);
		all->error = ft_strdup("1");
		ft_putstr("minishell: cd: HOME not set\n");
		return (NULL);
	}
	if (!(tmp = (char *)malloc(sizeof(char) *
		(ft_strlen(all->env[all->env_home_dir]) + 1))))
		ft_malloc_error();
	while (all->env[all->env_home_dir][i] != '\0')
	{
		tmp[j] = all->env[all->env_home_dir][i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int				ft_give_cd(t_commands *cmd, t_data *all)
{
	char	*tmp;
	char	res[1000];

	getcwd(res, 1000);
	if (cmd->arg[1])
	{
		if (cmd->arg[1][0] == '~')
			ft_give_tilda(cmd, all);
		if (chdir(cmd->arg[1]) == -1)
		{
			free(all->error);
			all->error = ft_strdup("1");
			ft_putstr("minishell: cd: ");
			ft_putstr(cmd->arg[1]);
			ft_putstr(": No such file or directory\n");
		}
	}
	else
	{
		if ((tmp = ft_env_replace_home(cmd, all)) != NULL)
			ft_er_cd(all, tmp);
		free(tmp);
	}
	ft_env_update(all, res);
	return (0);
}
