/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:00:51 by djast             #+#    #+#             */
/*   Updated: 2019/02/07 15:43:15 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		processing_minus(char *str, int width)
{
	write(1, "0x", 2);
	ft_putstr(str);
	while (width-- > ((int)ft_strlen(str) + 2))
		write(1, " ", 1);
}

static int		processing(char *result, int width, int precision, t_qual *qual)
{
	if (!QZ)
		while (width-- > ((int)ft_strlen(result) + 2))
			write(1, " ", 1);
	write(1, "0x", 2);
	if (ft_strcmp(result, "0") == 0 && QZ)
		while (width-- > ((int)ft_strlen(result) + 2))
			write(1, "0", 1);
	if (ft_strcmp(result, "0") != 0)
	{
		if (precision > 0)
			while (precision-- - (int)ft_strlen(result) > 0)
				write(1, "0", 1);
		ft_putstr(result);
		return (0);
	}
	else if (ft_strcmp(result, "0") == 0 && precision > 0)
	{
		while (precision-- > 0)
			write(1, "0", 1);
		return (QPR + 2);
	}
	else if (ft_strcmp(result, "0") == 0 && precision == 0)
		return (2);
	else
	{
		ft_putstr(result);
		return (0);
	}
}

int				ft_p(long long addr, t_qual *qual)
{
	char	*result;
	int		length;
	int		width;
	int		precision;
	int		count;

	precision = QPR;
	width = QW;
	count = 0;
	result = ft_translation(addr, 16);
	if (QM)
		processing_minus(result, width);
	else
		count = processing(result, width, precision, qual);
	if (!count)
	{
		length = QPR > 0 ?
		QPR + 2 : ft_strlen(result) + 2;
		free(result);
		return (QW > length ? QW : length);
	}
	return (count);
}
