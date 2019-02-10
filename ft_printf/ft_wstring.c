/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:36:02 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/08 18:55:56 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_wstrlen(wchar_t *str, int precision, int i)
{
	if (*str == '\0' || precision == 0)
		return (i);
	else if (*str <= 127)
		return (calc_wstrlen(str + 1, precision - 1, i + 1));
	else if (*str <= 2047 && precision >= 2)
		return (calc_wstrlen(str + 1, precision - 2, i + 2));
	else if (*str <= 65535 && precision >= 3)
		return (calc_wstrlen(str + 1, precision - 3, i + 3));
	else if (*str <= 2097151 && precision >= 4)
		return (calc_wstrlen(str + 1, precision - 4, i + 4));
	else
		return (i);
}

static int	ft_wstrlen(wchar_t *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str <= 127)
			i++;
		else if (*str <= 2047)
			i += 2;
		else if (*str <= 65535)
			i += 3;
		else if (*str <= 2097151)
			i += 4;
		str++;
	}
	return (i);
}

static void	ft_putwchar(wchar_t c)
{
	unsigned char put[4];

	if (c <= 127)
		write(1, &c, 1);
	else if (c <= 2047)
	{
		put[0] = (c >> 6) + 192;
		put[1] = ((c & 63) + 128);
		write(1, put, 2);
	}
	else if (c <= 65535)
	{
		put[0] = (c >> 12) + 224;
		put[1] = ((c >> 6) & 63) + 128;
		put[2] = ((c & 63) + 128);
		write(1, put, 3);
	}
	else if (c <= 2097151)
	{
		put[0] = (c >> 18) + 240;
		put[1] = ((c >> 12) & 63) + 128;
		put[2] = ((c >> 6) & 63) + 128;
		put[3] = ((c & 63) + 128);
		write(1, put, 4);
	}
}

static void	ft_putnwstr(const wchar_t *str, int len)
{
	int	i;

	i = 0;
	while (*str && i < len)
	{
		if (*str <= 127)
			i++;
		else if (*str <= 2047)
			i += 2;
		else if (*str <= 65535)
			i += 3;
		else if (*str <= 2097151)
			i += 4;
		if (i <= len)
			ft_putwchar(*str++);
	}
}

int			ft_ws(wchar_t *str, t_qual *qual)
{
	int		lenght;
	int		width;

	if (str == NULL)
		str = L"(null)";
	lenght = QPR >= 0 ?
	calc_wstrlen(str, QPR, 0) : ft_wstrlen(str);
	width = QW - lenght;
	if (QW > 0 && !QM)
	{
		if (QZ)
			while (width-- > 0)
				write(1, "0", 1);
		else
			while (width-- > 0)
				write(1, " ", 1);
	}
	ft_putnwstr(str, lenght);
	if (QW > 0 && QM)
		while (width-- > 0)
			write(1, " ", 1);
	return (QW > 0 ? ft_max(2, lenght, QW) : lenght);
}
