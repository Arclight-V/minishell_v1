/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:47:54 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/29 21:23:20 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_str_check_exp(t_data *all, char **env, char *arg)
{
	int i;
	int g;

	i = 0;
	if (ft_supercheck_arg(arg) == 1)
		return (ft_utils_check(all, arg));
	while (env[i])
	{
		g = 0;
		while (env[i][g] == arg[g])
		{
			g++;
			if (env[i][g] == '=' && arg[g] == '=')
				return (2);
			if (env[i][g] == '=' && arg[g] == '\0')
				return (1);
			if (env[i][g] == '\0' && arg[g] == '=')
				return (2);
			if (env[i][g] == '\0' && arg[g] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int				ft_str_check_uns(char *str, char **arg)
{
	int	i;
	int	g;
	int	count;

	if (str == NULL)
		return (1);
	count = 1;
	i = ft_strlen_msv(arg);
	while (i != 1)
	{
		g = 0;
		while (str[g] == arg[count][g])
		{
			g++;
			if (arg[count][g] == '=' && str[g] == '=')
				return (1);
			if (arg[count][g] == '\0' && str[g] == '\0')
				return (1);
			if (arg[count][g] == '=' && str[g] == '\0')
				return (1);
		}
		count++;
		i--;
	}
	return (0);
}

static int		ft_str_check_unset(char *str, char **arg)
{
	int	i;
	int	g;
	int	count;

	if (str == NULL)
		return (0);
	count = 1;
	i = ft_strlen_msv(arg);
	while (i != 1)
	{
		g = 0;
		while (str[g] == arg[count][g])
		{
			g++;
			if (arg[count][g] == '=' && str[g] == '=')
				return (1);
			if (arg[count][g] == '\0' && str[g] == '=')
				return (1);
			if (arg[count][g] == '\0' && str[g] == '\0')
				return (1);
		}
		count++;
		i--;
	}
	return (0);
}

static void		ft_give_unsets(t_commands *cmd, t_data *all)
{
	char	**tmp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!(tmp = (char **)malloc(sizeof(char*) * (ft_strlen_msv(all->env) + 1))))
		ft_malloc_error();
	while (all->env[count] != NULL)
	{
		if (ft_str_check_unset(all->env[count], cmd->arg) != 1)
		{
			tmp[i] = ft_strdup(all->env[count]);
			i++;
		}
		count++;
	}
	tmp[i] = NULL;
	free_msv(all->env);
	all->env = NULL;
	all->env = tmp;
}

int				ft_give_unset(t_commands *cmd, t_data *all)
{
	int i;

	i = 1;
	while (cmd->arg[i])
	{
		if (ft_supercheck_arg(cmd->arg[i]) == 1)
		{
			write(1, "minishell: export: `", 20);
			ft_putstr(cmd->arg[i]);
			write(1, "': not a valid identifier\n", 26);
			free(all->error);
			all->error = ft_strdup("1");
		}
		i++;
	}
	ft_give_unsets(cmd, all);
	return (0);
}
