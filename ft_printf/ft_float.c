/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:03:09 by djast             #+#    #+#             */
/*   Updated: 2019/02/07 15:43:25 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_f(long double d, t_qual *qual)
{
	intmax_t	first;
	long double	last;
	int			i;

	i = 0;
	first = d / 1;
	last = d - (int)d;
	if (ft_strcmp(QL, "l") == 0 || ft_strcmp(QL, "") == 0)
	{
		ft_putllnbr(first);
		write(1, ".", 1);
		while (i++ != 6)
		{
			ft_putllnbr((last * 10 - (int)last));
			last = last * 10 - (int)(last * 10);
		}
	}
	else if (ft_strcmp(QL, "L") == 0)
	{
		ft_putllnbr(first);
		write(1, ".", 1);
		while (i++ != 6)
		{
			ft_putllnbr((last * 10 - (int)last));
			last = last * 10 - (int)(last * 10);
		}
	}
	return (0);
}
