/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:59:13 by djast             #+#    #+#             */
/*   Updated: 2019/02/04 18:24:41 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_size_by_lenght(intmax_t nbr, t_qual *qual)
{
	if (ft_strcmp(qual->lenght, "ll") == 0)
		nbr = (long long int)nbr;
	else if (ft_strcmp(qual->lenght, "l") == 0)
		nbr = (long int)nbr;
	else if (ft_strcmp(qual->lenght, "h") == 0)
		nbr = (short int)nbr;
	else if (ft_strcmp(qual->lenght, "hh") == 0)
		nbr = (signed char)nbr;
	else if (ft_strcmp(qual->lenght, "j") == 0)
		nbr = (intmax_t)nbr;
	else if (ft_strcmp(qual->lenght, "z") == 0)
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

void		ft_print_width(t_qual *qual, int size_nbr)
{
	int		width;
	int		precision;
	char	print_char;

	if (qual->plus == 1 && qual->sign == 0 && qual->precision == -1 &&
	qual->zero == 1 && qual->minus == 0 && qual->unsint == 0)
		write(1, "+", 1);
	//printf("%d %d %d %d\n", qual->space, qual->sign, qual->plus, qual->unsint);
	if (qual->space == 1 && qual->sign == 0 &&
	qual->plus == 0 && qual->unsint == 0)
		write(1, " ", 1);
	if (qual->sign == 1 && qual->precision == -1 &&
	(qual->width == -1 || qual->zero == 1) &&
	qual->minus == 0 && qual->unsint == 0)
		write(1, "-", 1);
	if (qual->precision == -1 && qual->zero == 1 && qual->minus == 0)
		print_char = '0';
	else
		print_char = ' ';
	precision = qual->precision < size_nbr ? size_nbr : qual->precision;
	width = qual->plus == 1 ? qual->width - precision - 1 + qual->unsint :
	qual->width - precision - qual->sign - qual->space;
	while (width-- > 0)
		write(1, &print_char, 1);
	if (qual->sign == 1 && qual->precision == -1 && qual->width != -1 &&
	qual->zero == 0 && qual->unsint == 0 && qual->minus == 0)
		write(1, "-", 1);
	if (qual->plus == 1 && qual->sign == 0 && qual->precision == -1 &&
	qual->zero == 0 && qual->unsint == 0 && qual->minus == 0)
		write(1, "+", 1);
}

void		ft_print_presicion(t_qual *qual, int size_nbr)
{
	int real_precision;

	if (qual->plus == 1 && qual->sign == 0 && qual->unsint == 0 &&
	(qual->precision != -1 || qual->minus == 1))
		write(1, "+", 1);
	if (qual->sign == 1 &&
	(qual->precision != -1 || qual->minus == 1) && qual->unsint == 0)
		write(1, "-", 1);
	real_precision = qual->precision - size_nbr;
	while (real_precision-- > 0)
		write(1, "0", 1);
}

int			ft_d(intmax_t nbr, t_qual *qual)
{
	int size_nbr;

	nbr = ft_size_by_lenght(nbr, qual);
	qual->sign = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	size_nbr = ft_num_size(nbr);
	if (qual->minus == 0 || (qual->minus == 1 && qual->space == 1))
	{
		ft_print_width(qual, size_nbr);
		ft_print_presicion(qual, size_nbr);
		if (nbr != 0 || qual->precision != 0)
			ft_putllnbr(nbr);
		if (nbr == 0 && qual->width != -1 && qual->precision == 0)
			write(1, " ", 1);
	}
	else
	{
		ft_print_presicion(qual, size_nbr);
		if (nbr != 0 || qual->precision != 0)
			ft_putllnbr(nbr);
		ft_print_width(qual, size_nbr);
	}
	if (nbr == 0 && qual->precision == 0)
		size_nbr--;
	return (qual->space == 1 || qual->plus == 1) && qual->sign == 0 ?
	ft_max(3, qual->width, qual->precision, size_nbr + qual->sign + 1) :
	ft_max(3, qual->width, qual->precision + qual->sign, size_nbr + qual->sign);
}
