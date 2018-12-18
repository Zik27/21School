/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:25:53 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:13:49 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(int n)
{
	int	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		length;
	int		tmp;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmp = n;
	length = get_length(n);
	if (n < 0)
	{
		tmp = -n;
		length++;
	}
	result = ft_strnew(length);
	if (!result)
		return (NULL);
	while (length--)
	{
		result[length] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (n < 0)
		*result = '-';
	return (result);
}
