/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:57:18 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/06 12:04:08 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	sym;
	char	*tmp;

	sym = c;
	tmp = NULL;
	while (1)
	{
		if (*s == sym)
			tmp = (char *)s;
		if (*s++ == '\0')
			break ;
	}
	return (tmp);
}
