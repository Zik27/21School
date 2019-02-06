/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:46:12 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/06 14:13:54 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		oct_4(wint_t c)
{
	unsigned char put[4];

	put[0] = (c >> 18) + 240;
	put[1] = ((c >> 12) & 63) + 128;
	put[2] = ((c >> 6) & 63) + 128;
	put[3] = ((c & 63) + 128);
	write(1, put, 4);
}

static void		oct_3(wint_t c)
{
	unsigned char put[3];

	put[0] = (c >> 12) + 224;
	put[1] = ((c >> 6) & 63) + 128;
	put[2] = ((c & 63) + 128);
	write(1, put, 3);
}

static void		oct_2(wint_t c)
{
	unsigned char put[2];

	put[0] = (c >> 6) + 192;
	put[1] = ((c & 63) + 128);
	write(1, put, 2);
}

static void		print_width(int width)
{
	while (width-- > 0)
		write(1, " ", 1);
}

int				ft_wc(wint_t c, t_qual *qual)
{
	int	lenght;

	if (c <= 127)
	{
		if (!qual->minus)
			print_width(qual->width - 1);
		write(1, &c, 1);
		if (qual->minus)
			print_width(qual->width - 1);
		lenght = 1;
	}
	if (c >= 127 && c <= 2047)
	{
		if (!qual->minus)
			print_width(qual->width - 2);
		oct_2(c);
		if (qual->minus)
			print_width(qual->width - 2);
		lenght = 2;
	}
	if (c >= 2048 && c <= 65535)
	{
		if (!qual->minus)
			print_width(qual->width - 3);
		oct_3(c);
		if (qual->minus)
			print_width(qual->width - 3);
		lenght = 3;
	}
	if (c >= 65536 && c <= 2097151)
	{
		if (!qual->minus)
			print_width(qual->width - 4);
		oct_4(c);
		if (qual->minus)
			print_width(qual->width - 4);
		lenght = 4;
	}
	if (qual->width > lenght)
		return (qual->width);
	return (lenght);
}