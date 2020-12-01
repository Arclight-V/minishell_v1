/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:45:58 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 15:04:56 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list		*line_to_lst(char *line, int *er, t_data *all)
{
	t_list	*i_map;
	t_list	*point_list;
	char	*w;

	point_list = NULL;
	while ((w = get_word(&line, er, all)))
	{
		i_map = ft_lstnew(w);
		ft_lstadd_back(&point_list, i_map);
	}
	return (point_list);
}

char		**line_to_mas(char *line, int *er, t_data *all)
{
	char	**map;
	t_list	*point_list;
	int		size;
	int		i;
	void	*next;

	point_list = line_to_lst(line, er, all);
	size = ft_lstsize(point_list);
	map = (char**)ft_calloc(sizeof(char*) * (size + 1), 1);
	map[size] = NULL;
	i = 0;
	while (size != i)
	{
		map[i] = point_list->content;
		i++;
		next = point_list->next;
		free(point_list);
		point_list = next;
	}
	return (map);
}
