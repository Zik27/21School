/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:04:04 by djast             #+#    #+#             */
/*   Updated: 2019/02/06 20:02:53 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_upper_str(char *str)
{
	char *begin;

	begin = str;
	while (*str)
	{
		if (*str >= 97 && *str <= 122)
			*str = *str - 32;
		str++;
	}
	return (begin);
}

// static int		hex_check_zero(char **result_str, t_qual *qual, int flag)
// {
// 	int		size;
// 	char	*tmp;

// 	tmp = *result_str;
// 	size = ft_strcmp(*result_str, "0") == 0 ? 0 : (int)ft_strlen(*result_str);
// 	if (qual->hash == 1 && ft_strcmp(*result_str, "0") != 0 && !qual->zero)
// 	{
// 		size += 2;
// 		*result_str = ft_strjoin("0x", *result_str);
// 		free(tmp);
// 	}
// 	else if (qual->hash == 1 && ft_strcmp(*result_str, "0") != 0 &&
// 	qual->zero == 1)
// 	{
// 		size += 2;
// 		if (flag)
// 			write(1, "0X", 2);
// 		else
// 			write(1, "0x", 2);
// 	}
// 	return (size);
// }

// static void		hex_check_width(t_qual *qual, int size)
// {
// 	int width;

// 	width = qual->width - size;
// 	if (qual->width > 0 && qual->precision >= 0)
// 	{
// 		if (qual->precision > size)
// 		{
// 			width = qual->width - qual->precision;
// 			while (width-- > 0)
// 				write(1, " ", 1);
// 		}
// 		else
// 			while (width-- > 0)
// 				write(1, " ", 1);
// 	}
// 	else if (qual->precision == -1 && qual->width > 0)
// 	{
// 		width = qual->width - size;
// 		if (qual->zero == 1 && !qual->minus)
// 			while (width-- > 0)
// 				write(1, "0", 1);
// 		else if (!qual->zero || (qual->zero == 1 && qual->minus == 1))
// 			while (width-- > 0)
// 				write(1, " ", 1);
// 	}
// }

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

int				ft_x(intmax_t numb, int flag, t_qual *qual)
{
	char	*result_str;
	int		tmp;
	int		lenght_wide;
	int		lenght_prec;
	int		value_ret;

	result_str = check_modifier(numb, qual);
	lenght_wide = qual->hash && ft_strcmp(result_str, "0") != 0 ? ft_strlen(result_str) + 2 : ft_strlen(result_str);
	lenght_prec = ft_strlen(result_str);
	if (!qual->minus && qual->width > 0)
	{
		if (qual->precision > 0 && lenght_prec < qual->precision && (!qual->hash || ft_strcmp(result_str, "0") == 0))
			tmp = qual->width - qual->precision;
		else if (qual->precision > 0 && lenght_prec < qual->precision && qual->hash && ft_strcmp(result_str, "0") != 0)
			tmp = qual->width - qual->precision - 2;
		else
			tmp = qual->width - lenght_wide;
		if (qual->zero && qual->precision == -1)
			while (tmp-- > 0)
				write(1, "0", 1);
		else
			while (tmp-- > 0)
				write(1, " ", 1);
	}
	tmp = qual->precision;
	if (qual->hash && ft_strcmp(result_str, "0") != 0)
		write(1, flag ? "0X" : "0x", 2);
	if (tmp > 0)
		while (tmp-- - lenght_prec > 0)
			write(1, "0", 1);
	ft_putstr(flag ? ft_upper_str(result_str) : result_str);
	if (qual->minus && qual->precision < qual->width)
	{
		tmp = qual->width;
		while (tmp-- - lenght_wide > 0)
			write(1, " ", 1);
	}
	value_ret = ft_max(2, qual->precision, lenght_prec);
	if (qual->hash && ft_strcmp(result_str, "0") != 0)
		value_ret += 2;
	return (value_ret < qual->width ? qual->width : value_ret);
}




// int				ft_x(intmax_t numb, int flag, t_qual *qual)
// {
// 	char	*result_str;
// 	int		size;
// 	int		precision;
// 	int		lenght;

// 	precision = qual->precision;
// 	result_str = check_modifier(numb, qual);
// 	size = hex_check_zero(&result_str, qual, flag);
// 	if (!qual->minus)
// 		hex_check_width(qual, size);
// 	if (precision > size)
// 		while (precision-- - size > 0)
// 			write(1, "0", 1);
// 	if (ft_strcmp(result_str, "0") == 0 && qual->precision == 0)
// 	{
// 		free(result_str);
// 		return (qual->width == -1 ? 0 : qual->width);
// 	}
// 	ft_putstr(flag ? ft_upper_str(result_str) : result_str);
// 	lenght = ft_strlen(result_str);
// 	if (qual->minus == 1)
// 		hex_check_width(qual, size);
// 	free(result_str);
// 	return (lenght == 0 && qual->width == -1 && qual->precision != -1 ?
// 	0 : ft_max(3, qual->width, qual->precision, lenght));
// }

