/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 19:01:33 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:25:49 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int a;

	a = 0;
	while (src[a] != '\0' && a < len)
	{
		dst[a] = src[a];
		a++;
	}
	while (a < len)
	{
		dst[a] = '\0';
		a++;
	}
	return (dst);
}
