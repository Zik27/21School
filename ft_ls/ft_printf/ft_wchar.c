/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:46:12 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/08 18:55:50 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_value(wint_t c, int flag)
{
	unsigned char put[4];

	if (flag == 4)
	{
		put[0] = (c >> 18) + 240;
		put[1] = ((c >> 12) & 63) + 128;
		put[2] = ((c >> 6) & 63) + 128;
		put[3] = ((c & 63) + 128);
	}
	if (flag == 3)
	{
		put[0] = (c >> 12) + 224;
		put[1] = ((c >> 6) & 63) + 128;
		put[2] = ((c & 63) + 128);
	}
	if (flag == 2)
	{
		put[0] = (c >> 6) + 192;
		put[1] = ((c & 63) + 128);
	}
	if (flag == 1)
		put[0] = c;
	write(1, put, flag);
}

static void	print_width(int width)
{
	while (width-- > 0)
		write(1, " ", 1);
}

static void	check_other_value(wint_t c, int *lenght, t_qual *qual)
{
	if (c >= 2048 && c <= 65535)
	{
		if (!QM)
			print_width(QW - 3);
		print_value(c, 3);
		if (QM)
			print_width(QW - 3);
		*lenght = 3;
	}
	if (c >= 65536 && c <= 2097151)
	{
		if (!QM)
			print_width(QW - 4);
		print_value(c, 4);
		if (QM)
			print_width(QW - 4);
		*lenght = 4;
	}
}

int			ft_wc(wint_t c, t_qual *qual)
{
	int	lenght;

	if (c <= 127)
	{
		if (!QM)
			print_width(QW - 1);
		print_value(c, 1);
		if (QM)
			print_width(QW - 1);
		lenght = 1;
	}
	if (c >= 127 && c <= 2047)
	{
		if (!QM)
			print_width(QW - 2);
		print_value(c, 2);
		if (QM)
			print_width(QW - 2);
		lenght = 2;
	}
	else
		check_other_value(c, &lenght, qual);
	if (QW > lenght)
		return (QW);
	return (lenght);
}
