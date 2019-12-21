/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:59:55 by djast             #+#    #+#             */
/*   Updated: 2019/11/29 16:00:45 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*arr;

	arr = (char *)malloc(size * sizeof(*arr) + 1);
	if (arr == NULL)
		return (NULL);
	ft_bzero((void *)arr, size * sizeof(*arr) + 1);
	return (arr);
}
