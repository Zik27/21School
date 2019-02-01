/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:04:04 by djast             #+#    #+#             */
/*   Updated: 2019/02/01 17:57:25 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		hex_check_zero(char **result_str, t_qual *qual, int flag)
{
	int size;
	char *tmp;

	tmp = *result_str;
	size = ft_strcmp(*result_str, "0") == 0 ? 0 : (int)ft_strlen(*result_str);
	if (qual->hash == 1 && ft_strcmp(*result_str, "0") != 0 && !qual->zero)
	{
		size += 2;
		*result_str = ft_strjoin("0x", *result_str);
		free(tmp);
	}
	else if (qual->hash == 1 && ft_strcmp(*result_str, "0") != 0 &&
	qual->zero == 1)
	{
		size += 2;
		if (flag)
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
	return (size);
}

static void		hex_check_width(t_qual *qual, int size)
{
	int width;

	width = qual->width - size;
	if (qual->width > 0 && qual->precision >= 0)
	{
		if (qual->precision > size)
		{
			width = qual->width - qual->precision;
			while (width-- > 0)
				write(1, " ", 1);
		}
		else
			while (width-- > 0)
				write(1, " ", 1);
	}
	else if (qual->precision == -1 && qual->width > 0)
	{
		width = qual->width - size;
		if (qual->zero == 1 && !qual->minus)
			while (width-- > 0)
				write(1, "0", 1);
		else if (!qual->zero || (qual->zero == 1 && qual->minus == 1))
			while (width-- > 0)
				write(1, " ", 1);
	}
}

int			ft_x(intmax_t numb, int flag, t_qual *qual)
{
	char	*result_str;
	int		size;
	int		tmp;
	int		lenght;

	tmp = qual->precision;



	numb = ft_size_by_lenght(numb, qual);
	if (ft_strcmp(qual->lenght, "l") == 0)
		result_str = ft_translation((unsigned long int)numb, 16);
	else if (ft_strcmp(qual->lenght, "ll") == 0)
		result_str = ft_translation((unsigned long long int)numb, 16);
	else if (ft_strcmp(qual->lenght, "j") == 0)
		result_str = ft_translation(numb, 16);
	else if (ft_strcmp(qual->lenght, "h") == 0)
		result_str = ft_translation((unsigned short int)numb, 16);
	else if (ft_strcmp(qual->lenght, "hh") == 0)
		result_str = ft_translation((unsigned char)numb, 16);
	else if (ft_strcmp(qual->lenght, "z") == 0)
		result_str = ft_translation((size_t)numb, 16);
	else
		result_str = ft_translation((unsigned int)numb, 16);



	size = hex_check_zero(&result_str, qual, flag);
	if (!qual->minus)
		hex_check_width(qual, size);
	if (tmp > size)
		while (tmp-- - size > 0)
			write(1, "0", 1);
	if (ft_strcmp(result_str, "0") == 0 && qual->precision == 0)
	{
		free(result_str);
		return (qual->width == -1 ? 0 : qual->width);
	}
	if (flag)
		ft_upper_str(result_str);
	ft_putstr(result_str);
	lenght = ft_strlen(result_str);
	if (qual->minus == 1)
		hex_check_width(qual, size);
	free(result_str);
	return (lenght == 0 && qual->width == -1 && qual->precision != -1 ? 0 : ft_max(3, qual->width, qual->precision, lenght));
}
