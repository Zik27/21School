/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:13:10 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 15:43:55 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			size;
	int			result;
	int			sign;

	result = 0;
	size = 0;
	sign = 1;
	while (str[size] == ' ' || str[size] == '\t' || str[size] == '\n' ||\
	str[size] == '\v' || str[size] == '\f' || str[size] == '\r')
		size++;
	if (str[size] == '-')
		sign = -1;
	if (str[size] == '-' || str[size] == '+')
	{
		size++;
	}
	while (str[size] >= 48 && str[size] <= 57)
	{
		result = result * 10 + (str[size] - 48);
		size++;
	}
	return (sign * result);
}
