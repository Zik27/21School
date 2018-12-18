/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:50:49 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:37:25 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;
	size_t		i;

	tmp_dst = dst;
	tmp_src = src;
	i = 0;
	if (tmp_dst <= tmp_src)
		while (i++ < len)
			*tmp_dst++ = *tmp_src++;
	else
	{
		tmp_dst = tmp_dst + len - 1;
		tmp_src = tmp_src + len - 1;
		while (i++ < len)
			*tmp_dst-- = *tmp_src--;
	}
	return (dst);
}
