/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:53:18 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:17:23 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*tmp;
	char		*dst_tmp;

	tmp = src;
	dst_tmp = dst;
	while (n)
	{
		*dst_tmp++ = *tmp++;
		n--;
	}
	return (dst);
}
