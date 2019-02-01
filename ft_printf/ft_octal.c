/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:03:39 by djast             #+#    #+#             */
/*   Updated: 2019/02/01 15:56:20 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		octal_check_width(t_qual *qual, int size)
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

int ft_o(intmax_t numb, t_qual *qual)
{
	char *result_str;
	int		size;
	int		tmp;
	int lenght;

	tmp = qual->precision;

	numb = ft_size_by_lenght(numb, qual);

	if (ft_strcmp(qual->lenght, "l") == 0)
		result_str = ft_translation((unsigned long int)numb, 8);
	else if (ft_strcmp(qual->lenght, "ll") == 0)
		result_str = ft_translation((unsigned long long int)numb, 8);
	else if (ft_strcmp(qual->lenght, "h") == 0)
		result_str = ft_translation((unsigned short int)numb, 8);
	else if (ft_strcmp(qual->lenght, "hh") == 0)
		result_str = ft_translation((unsigned char)numb, 8);
	else if (ft_strcmp(qual->lenght, "j") == 0)
		result_str = ft_translation(numb, 8);
	else if (ft_strcmp(qual->lenght, "z") == 0)
		result_str = ft_translation((size_t)numb, 8);
	else
		result_str = ft_translation((unsigned int)numb, 8);




	if (qual->hash && ft_strcmp(result_str, "0") != 0)
		result_str = ft_strjoin("0", result_str);
	size = ft_strcmp(result_str, "0") == 0 ? 0 : (int)ft_strlen(result_str);

	if (!qual->minus)
		octal_check_width(qual, size);
	if (tmp > size)
		while (tmp-- - size > 0)
			write(1, "0", 1);
	if (ft_strcmp(result_str, "0") == 0 && qual->precision == 0 && !qual->hash)
	{
		free(result_str);
		return (qual->width == -1 ? 0 : qual->width);
	}
	else if (ft_strcmp(result_str, "0") == 0 && qual->precision == 0 && qual->hash)
	{
		write(1, "0", 1);
		free(result_str);
		return (qual->width == -1 ? 1 : qual->width);
	}
	ft_putstr(result_str);
	lenght = ft_strlen(result_str);
	if (qual->minus == 1)
		octal_check_width(qual, size);
	free(result_str);
	return (lenght == 0 && qual->width == -1 && qual->precision != -1 ? 0 : ft_max(3, qual->width, qual->precision, lenght));
}