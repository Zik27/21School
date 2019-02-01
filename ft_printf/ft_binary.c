/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:45:51 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/31 20:18:13 by vurrigon         ###   ########.fr       */
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

int		ft_b(intmax_t numb, t_qual *qual)
{
	char *result_str;
	int		size;
	int		tmp;
	int		length;

	tmp = qual->precision;

	numb = ft_size_by_lenght(numb, qual);

	if (ft_strcmp(qual->lenght, "l") == 0)
		result_str = ft_translation((unsigned long int)numb, 2);
	else if (ft_strcmp(qual->lenght, "ll") == 0)
		result_str = ft_translation((unsigned long long int)numb, 2);
	else
		result_str = ft_translation((unsigned int)numb, 2);
	if (qual->hash && ft_strcmp(result_str, "0") != 0)
		result_str = ft_strjoin("0", result_str);
	size = ft_strcmp(result_str, "0") == 0 ? 0 : (int)ft_strlen(result_str);

	if (!qual->minus)
		binary_check_width(qual, size);
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
	length = ft_strlen(result_str);
	if (qual->minus == 1)
		binary_check_width(qual, size);
	free(result_str);
	return (length == 0 && qual->width == -1 && qual->precision != -1 ? 0 : ft_max(3, qual->width, qual->precision, length));
}