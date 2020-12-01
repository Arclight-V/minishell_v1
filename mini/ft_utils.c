/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:29:34 by atomatoe          #+#    #+#             */
/*   Updated: 2020/10/28 13:47:00 by atomatoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strzero(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	**ft_strdup_msv(char **str)
{
	char	**tmp;
	int		count;

	count = 0;
	while (str[count])
		count++;
	if (!(tmp = (char **)malloc(sizeof(char*) * (count + 1))))
		ft_malloc_error();
	count = 0;
	while (str[count])
	{
		tmp[count] = ft_strdup(str[count]);
		count++;
	}
	tmp[count] = NULL;
	return (tmp);
}

int		ft_strlen_msv(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_compare_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		i++;
		if (s1[i] == '\0' && s2[i] == '\0')
			return (1);
	}
	return (-1);
}

char	**free_msv(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (str);
}
