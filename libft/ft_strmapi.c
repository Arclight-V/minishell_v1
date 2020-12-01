/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:19:23 by skarry            #+#    #+#             */
/*   Updated: 2020/10/28 15:13:42 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*pi;
	size_t	i;

	if (!s || !f)
		return (NULL);
	if (!(pi = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		ft_malloc_error();
	i = 0;
	while (s[i])
	{
		pi[i] = f(i, s[i]);
		i++;
	}
	pi[i] = '\0';
	return (pi);
}
