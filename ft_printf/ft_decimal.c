/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:59:13 by djast             #+#    #+#             */
/*   Updated: 2019/02/10 16:08:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_print_width(t_qual *qual, int size_nbr)
{
	int		width;
	int		precision;
	char	print_char;

	if (QPR == -1 && QZ == 1 && QM == 0)
		print_char = '0';
	else
		print_char = ' ';
	precision = QPR < size_nbr ? size_nbr : QPR;
	width = QPL == 1 || QSN ? QW - precision - 1 + QUS :
	QW - precision - QSN - QSP;
	while (width-- > 0)
	{
		if (QSP && QM && QW > size_nbr && QW > QPR)
			break ;
		write(1, &print_char, 1);
	}
	if (QSN == 1 && QPR == -1 && QW != -1 &&
	QZ == 0 && QUS == 0 && QM == 0)
		write(1, "-", 1);
	if (QPL == 1 && QSN == 0 && QPR == -1 &&
	QZ == 0 && QUS == 0 && QM == 0)
		write(1, "+", 1);
}

void			ft_print_spec_sign(t_qual *qual, int size_nbr)
{
	if (QPL == 1 && QSN == 0 && QPR == -1 &&
	QZ == 1 && QM == 0 && QUS == 0)
		write(1, "+", 1);
	if (QSP == 1 && QSN == 0 &&
	QPL == 0 && QUS == 0)
		write(1, " ", 1);
	if (QSN == 1 && QPR == -1 &&
	(QW == -1 || QZ == 1) &&
	QM == 0 && QUS == 0)
		write(1, "-", 1);
	ft_print_width(qual, size_nbr);
}

void			ft_print_presicion(t_qual *qual, int size_nbr)
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

static void		check_minus_space(t_qual *qual, int width,
					int size, intmax_t nbr)
{
	if (QM == 0 || (QM == 1 && QSP == 1))
	{
		ft_print_spec_sign(qual, size);
		ft_print_presicion(qual, size);
		if (nbr != 0 || QPR != 0)
			ft_putllnbr(nbr);
		if (QSP && QM && QW > size && QW > QPR && QPR == -1)
			while (width-- - size - 1 > 0)
				write(1, " ", 1);
		else if (QSP && QM && QW > size && QW > QPR && QPR > 0 && QPR > size)
			while (width-- - QPR - 1 > 0)
				write(1, " ", 1);
		else if (QSP && QM && QW > size && QW > QPR)
			while (width-- - size - 1 > 0)
				write(1, " ", 1);
		if (nbr == 0 && QW != -1 && QPR == 0)
			write(1, " ", 1);
	}
	else
	{
		ft_print_presicion(qual, size);
		if (nbr != 0 || QPR != 0)
			ft_putllnbr(nbr);
		ft_print_spec_sign(qual, size);
	}
}

int				ft_d(intmax_t nbr, t_qual *qual)
{
	int size_nbr;
	int value_ret;
	int width;

	nbr = ft_size_by_lenght(nbr, qual);
	QSN = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	size_nbr = ft_num_size(nbr);
	width = QW;
	check_minus_space(qual, width, size_nbr, nbr);
	if (nbr == 0 && QPR == 0)
		size_nbr--;
	value_ret = (QSP == 1 || QPL == 1) && QSN == 0 ?
	ft_max(3, QW, QPR, size_nbr + QSN + 1) :
	ft_max(3, QW, QPR + QSN, size_nbr + QSN);
	if ((QPL || QSP) && QPR > size_nbr && QW <= QPR && !QSN)
		value_ret++;
	return (value_ret);
}
