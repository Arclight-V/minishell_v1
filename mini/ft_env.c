/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:26:30 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/30 13:46:27 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	ft_init_struct(t_data *all)
{
	all->fd1 = dup(1);
	all->fd0 = dup(0);
	all->error = NULL;
	all->error = ft_strdup("0");
	all->home_dir = NULL;
	all->arg = NULL;
	all->env = NULL;
	all->env_home_dir = 0;
	all->env_dir_i = 0;
	all->env_old_dir_i = 0;
	all->env_path_i = 0;
	all->file_dir = NULL;
	g_status51 = 0;
}

void	ft_parse_env(t_data *all)
{
	int	i;

	i = 0;
	all->env_dir_i = -1;
	all->env_home_dir = -1;
	all->env_old_dir_i = -1;
	all->env_path_i = -1;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], "PWD=", 4) == 0)
			all->env_dir_i = i;
		if (ft_strncmp(all->env[i], "HOME=", 5) == 0)
			all->env_home_dir = i;
		if (ft_strncmp(all->env[i], "OLDPWD=", 7) == 0)
			all->env_old_dir_i = i;
		if (ft_strncmp(all->env[i], "PATH=", 5) == 0)
			all->env_path_i = i;
		i++;
	}
}

int		ft_creat_env(t_data *all, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (env[i])
		i++;
	if (!(all->env = (char **)malloc(sizeof(char*) * (i + 1))))
		ft_malloc_error();
	while (j != i)
	{
		all->env[j] = ft_strdup(env[j]);
		j++;
	}
	all->env[j] = NULL;
	ft_parse_env(all);
	if (all->env_home_dir != -1)
		all->home_dir = ft_strdup(all->env[all->env_home_dir]);
	return (0);
}

int		ft_utils_check(t_data *all, char *arg)
{
	write(1, "minishell: export: `", 20);
	ft_putstr(arg);
	write(1, "': not a valid identifier\n", 26);
	free(all->error);
	all->error = ft_strdup("1");
	return (1);
}
