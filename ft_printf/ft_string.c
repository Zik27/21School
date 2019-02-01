/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:02:10 by djast             #+#    #+#             */
/*   Updated: 2019/02/01 15:20:05 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_s(char *str, t_qual *qual)
{
	int real_width;
	int real_precision;

	real_width = qual->width;
	real_precision = qual->precision;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (real_precision >= 0)
		str = ft_strsub(str, 0, real_precision);
	if (qual->minus == 1)
	{
		write(1, str, ft_strlen(str));
		while (real_width-- > (int)ft_strlen(str))
			write(1, " ", 1);
	}
	else
	{
		if (qual->zero)
			while (real_width-- > (int)ft_strlen(str))
				write(1, "0", 1);
		else
			while (real_width-- > (int)ft_strlen(str))
				write(1, " ", 1);
		write(1, str, ft_strlen(str));
	}
	if ((qual->width == -1 && qual->precision > (int)ft_strlen(str)) || qual->width < (int)ft_strlen(str))
		return (ft_strlen(str));
	else if (qual->width > (int)ft_strlen(str))
		return (qual->width);
	return (ft_strlen(str) == 0 && qual->width == -1 && qual->precision != -1 ? 0 : ft_max(3, qual->width, qual->precision, ft_strlen(str)));
}