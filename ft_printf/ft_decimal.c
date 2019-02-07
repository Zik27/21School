/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:59:13 by djast             #+#    #+#             */
/*   Updated: 2019/02/07 20:26:36 by vurrigon         ###   ########.fr       */
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

void		ft_print_width(t_qual *qual, int size_nbr)
{
	int		width;
	int		precision;
	char	print_char;

	if (QPL == 1 && QSN == 0 && QPR == -1 &&
	QZ == 1 && QM == 0 && QUS == 0)
		write(1, "+", 1);
	//printf("%d %d %d %d\n", QSP, QSN, QPL, QUS);
	if (QSP == 1 && QSN == 0 &&
	QPL == 0 && QUS == 0)
		write(1, " ", 1);
	if (QSN == 1 && QPR == -1 &&
	(QW == -1 || QZ == 1) &&
	QM == 0 && QUS == 0)
		write(1, "-", 1);
	if (QPR == -1 && QZ == 1 && QM == 0)
		print_char = '0';
	else
		print_char = ' ';
	precision = QPR < size_nbr ? size_nbr : QPR;
	//printf("prec = %d\n", precision);
	width = QPL == 1 || QSN ? QW - precision - 1 + QUS :
	QW - precision - QSN - QSP;
	while (width-- > 0)
		write(1, &print_char, 1);
	if (QSN == 1 && QPR == -1 && QW != -1 &&
	QZ == 0 && QUS == 0 && QM == 0)
		write(1, "-", 1);
	if (QPL == 1 && QSN == 0 && QPR == -1 &&
	QZ == 0 && QUS == 0 && QM == 0)
		write(1, "+", 1);
}

void		ft_print_presicion(t_qual *qual, int size_nbr)
{
	int real_precision;

	if (QPL == 1 && QSN == 0 && QUS == 0 &&
	(QPR != -1 || QM == 1))
		write(1, "+", 1);
	if (QSN == 1 &&
	(QPR != -1 || QM == 1) && QUS == 0)
		write(1, "-", 1);
	real_precision = QPR - size_nbr;
	while (real_precision-- > 0)
		write(1, "0", 1);
}

int			ft_d(intmax_t nbr, t_qual *qual)
{
	int size_nbr;
	int value_ret;

	nbr = ft_size_by_lenght(nbr, qual);
	QSN = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	size_nbr = ft_num_size(nbr);
	if (QM == 0 || (QM == 1 && QSP == 1))
	{
		ft_print_width(qual, size_nbr);
		ft_print_presicion(qual, size_nbr);
		if (nbr != 0 || QPR != 0)
			ft_putllnbr(nbr);
		if (nbr == 0 && QW != -1 && QPR == 0)
			write(1, " ", 1);
	}
	else
	{
		ft_print_presicion(qual, size_nbr);
		if (nbr != 0 || QPR != 0)
			ft_putllnbr(nbr);
		ft_print_width(qual, size_nbr);
	}
	if (nbr == 0 && QPR == 0)
		size_nbr--;
	value_ret = (QSP == 1 || QPL == 1) && QSN == 0 ?
	ft_max(3, QW, QPR, size_nbr + QSN + 1) :
	ft_max(3, QW, QPR + QSN, size_nbr + QSN);
	if ((QPL || QSP) && QPR > size_nbr && QPR > QW && !QSN)
		value_ret++;
	return (value_ret);
}
