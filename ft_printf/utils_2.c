/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:51:40 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/08 21:21:25 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_size_by_lenght(intmax_t nbr, t_qual *qual)
{
	if (ft_strcmp(QL, "ll") == 0)
		nbr = (long long int)nbr;
	else if (ft_strcmp(QL, "l") == 0)
		nbr = (long int)nbr;
	else if (ft_strcmp(QL, "h") == 0)
		nbr = (short int)nbr;
	else if (ft_strcmp(QL, "hh") == 0)
		nbr = (signed char)nbr;
	else if (ft_strcmp(QL, "j") == 0)
		nbr = (intmax_t)nbr;
	else if (ft_strcmp(QL, "z") == 0)
		nbr = (size_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

intmax_t	ft_max(int count, ...)
{
	int			max;
	int			num;
	va_list		argptr;

	va_start(argptr, count);
	max = va_arg(argptr, intmax_t);
	while (--count)
	{
		num = va_arg(argptr, intmax_t);
		if (max < num)
			max = num;
	}
	return (max);
}
