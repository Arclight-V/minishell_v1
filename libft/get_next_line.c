/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:29:10 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 15:55:30 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*add_char_to_str(char *str, char c, int *size)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = (char *)malloc(sizeof(char) * (*size) + 1)))
		ft_malloc_error();
	while (str && i < (*size))
	{
		res[i] = str[i];
		i++;
	}
	free(str);
	str = NULL;
	res[*size] = c;
	*size += 1;
	return (res);
}

static int		ft_bytesnull(char ***line)
{
	if (!(**line = (char *)malloc(1)))
		ft_malloc_error();
	**line[0] = '\0';
	return (0);
}

static int		ft_bytenull(char **tmp, char ***line, int *size)
{
	*tmp = add_char_to_str(*tmp, '\0', &*size);
	**line = *tmp;
	return (0);
}

static int		base_cycle(char **line, char **tmp, char *buffer, int *size)
{
	if (buffer[0] == '\n')
	{
		if (!(*tmp = add_char_to_str(*tmp, '\0', size)))
			return (-1);
		*line = *tmp;
		return (1);
	}
	if (!(*tmp = add_char_to_str(*tmp, buffer[0], size)))
		return (-1);
	return (0);
}

int				get_next_line(char **line)
{
	char	buffer[1];
	int		bytes;
	int		size;
	char	*tmp;
	int		i;

	size = 0;
	tmp = NULL;
	while ((bytes = read(0, buffer, 1)) > 0)
		if ((i = base_cycle(line, &tmp, buffer, &size)) != 0)
			return (i);
	if (bytes == -1)
	{
		if (tmp)
			free(tmp);
		return (-1);
	}
	else if (bytes == 0)
	{
		if (!tmp)
			return (ft_bytesnull(&line));
		else
			return (ft_bytenull(&tmp, &line, &size));
	}
	return (-1);
}
