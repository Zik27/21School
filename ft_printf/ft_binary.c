/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:45:51 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/04 14:34:50 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		binary_check_width(t_qual *qual, int size)
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

static	char	*check_modifier(intmax_t numb, t_qual *qual)
{
	char	*result_str;

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
	return (result_str);
}

static	int		check_zwp_begin(char **res_str, t_qual *qual)
{
	int		size;
	int		precision;

	precision = qual->precision;
	if (qual->hash && ft_strcmp(*res_str, "0") != 0)
		*res_str = ft_strjoin("0", *res_str);
	size = ft_strcmp(*res_str, "0") == 0 ? 0 : (int)ft_strlen(*res_str);
	if (!qual->minus)
		binary_check_width(qual, size);
	if (precision > size)
		while (precision-- - size > 0)
			write(1, "0", 1);
	return (size);
}

int				ft_b(intmax_t numb, t_qual *qual)
{
	char	*res_str;
	int		size;
	int		length;

	res_str = check_modifier(numb, qual);
	size = check_zwp_begin(&res_str, qual);
	if (ft_strcmp(res_str, "0") == 0 && qual->precision == 0 && !qual->hash)
	{
		free(res_str);
		return (qual->width == -1 ? 0 : qual->width);
	}
	else if (ft_strcmp(res_str, "0") == 0 && qual->precision == 0 && qual->hash)
	{
		write(1, "0", 1);
		free(res_str);
		return (qual->width == -1 ? 1 : qual->width);
	}
	ft_putstr(res_str);
	length = ft_strlen(res_str);
	if (qual->minus == 1)
		binary_check_width(qual, size);
	free(res_str);
	return (length == 0 && qual->width == -1 && qual->precision != -1 ?
	0 : ft_max(3, qual->width, qual->precision, length));
}
