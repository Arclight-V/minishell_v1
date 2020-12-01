/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:54:39 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/29 21:18:25 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_str_replace(char **env, int i, int g)
{
	char	*str;

	str = ft_strdup(env[i]);
	free(env[i]);
	env[i] = NULL;
	env[i] = ft_strdup(env[g]);
	free(env[g]);
	env[g] = NULL;
	env[g] = ft_strdup(str);
	free(str);
	str = NULL;
	return (env);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

int		ft_supercheck_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (arg[0] == '=')
		return (1);
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[0] != '_' && (ft_isalpha(arg[0]) != 1))
			return (1);
		if (arg[i] != '_' && ft_isalpha(arg[i]) != 1
			&& ft_isdigit(arg[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_signal(int sig)
{
	int	pid;
	int	flag;

	g_status51 = 1;
	pid = waitpid(-1, &flag, WNOHANG);
	if (sig == SIGINT)
	{
		flag = 1;
		ft_putstr_fd("\b\b  \b\b", 1);
		if (pid)
		{
			ft_putstr_fd("\n", 1);
			ft_putstr_fd(_YEL_, 1);
			ft_putstr_fd(BOLD, 1);
			ft_putstr_fd("shell> ", 1);
			ft_putstr_fd(_DEF_, 1);
		}
	}
}

void	ft_signal_quit(int sig)
{
	int	pid;
	int	flag;

	(void)sig;
	pid = waitpid(-1, &flag, WNOHANG);
	if (!pid)
		ft_putendl_fd("Quit: 3", 1);
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}
