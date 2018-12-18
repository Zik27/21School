/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:35:13 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:16:31 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tmp_str;

	tmp_str = s;
	while (n--)
	{
		if (*tmp_str != (unsigned char)c)
			tmp_str++;
		else
			return ((void *)tmp_str);
	}
	return (NULL);
}
