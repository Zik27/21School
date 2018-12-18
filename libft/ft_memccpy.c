/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:21:31 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:15:49 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst_tmp;
	const unsigned char	*src_tmp;

	dst_tmp = dst;
	src_tmp = src;
	while (n)
	{
		*dst_tmp++ = *src_tmp;
		if (*src_tmp == (unsigned char)c)
			return (dst_tmp);
		src_tmp++;
		n--;
	}
	return (NULL);
}
