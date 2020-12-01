/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatashi <anatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:10 by anatashi          #+#    #+#             */
/*   Updated: 2020/12/01 20:14:39 by anatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_struct_data(void)
{
	t_data *new_struct;

	new_struct = (t_data *)ft_calloc(sizeof(t_data), 1);
	new_struct->fd_1 = dup(1);
	new_struct->fd_0 = dup(0);
	return (new_struct);
}
