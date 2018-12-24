/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:38:21 by vurrigon          #+#    #+#             */
/*   Updated: 2018/11/30 18:25:45 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	void	*buf;

	buf = (void *)malloc(size + 1);
	if (!buf)
		return (NULL);
	ft_bzero(buf, size + 1);
	return ((char *)buf);
}
