/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatashi <anatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:37:28 by anatashi          #+#    #+#             */
/*   Updated: 2020/12/01 20:15:55 by anatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_env(t_data *data)
{
	int 	i;

	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			data->current_pwd = i;
		else if (!ft_strncmp(data->envp[i], "HOME=", 5))
			data->home_dir = i;
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7)) 
			data->old_pwd = i;
		else if (!ft_strncmp(data->envp[i], "PATH=", 5))
			data->path = i;
		if (ft_strncmp((data)->envp[i], "_=", 2) == 0)
			data->env_var = i;
	}
	data->count_str = i;
}

void		create_env(t_data *data, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (envp[i])
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	while (++j != i)
		data->envp[j] = ft_strdup(envp[j]);
	data->envp[j] = NULL;
	parse_env(data);
}