/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:02:10 by djast             #+#    #+#             */
/*   Updated: 2019/02/04 17:07:24 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_minus(t_qual *qual, char *str)
{
	int real_width;

	real_width = qual->width;
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
}

int				ft_s(char *str, t_qual *qual)
{
	int real_precision;

	real_precision = qual->precision;
	if (!str)
		str = "(null)";
	if (real_precision >= 0)
		str = ft_strsub(str, 0, real_precision);
	check_minus(qual, str);
	if ((qual->width == -1 && qual->precision > (int)ft_strlen(str))
	|| qual->width < (int)ft_strlen(str))
		return (ft_strlen(str));
	else if (qual->width > (int)ft_strlen(str))
		return (qual->width);
	return (ft_strlen(str) == 0 && qual->width == -1 &&
	qual->precision != -1 ? 0 :
	ft_max(3, qual->width, qual->precision, ft_strlen(str)));
}
