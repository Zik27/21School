/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:30:13 by vurrigon          #+#    #+#             */
/*   Updated: 2018/11/20 19:50:17 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	length;
	int	*arr;

	i = 0;
	length = max - min;
	if (min >= max)
		return (NULL);
	arr = (int *)malloc(sizeof(int) * length + 1);
	while (i < length)
	{
		arr[i] = min + i;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
