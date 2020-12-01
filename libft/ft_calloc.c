/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:57:22 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 15:10:35 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t b)
{
	unsigned char	*s;

	if (!(s = (unsigned char*)malloc(n * b)))
		ft_malloc_error();
	ft_memset(s, 0, n * b);
	return (s);
}
