/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:45:51 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/07 15:43:17 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		binary_check_width(t_qual *qual, int size)
{
	int width;

	width = QW - size;
	if (QW > 0 && QPR >= 0)
	{
		if (QPR > size)
		{
			width = QW - QPR;
			while (width-- > 0)
				write(1, " ", 1);
		}
		else
			while (width-- > 0)
				write(1, " ", 1);
	}
	else if (QPR == -1 && QW > 0)
	{
		width = QW - size;
		if (QZ == 1 && !QM)
			while (width-- > 0)
				write(1, "0", 1);
		else if (!QZ || (QZ == 1 && QM == 1))
			while (width-- > 0)
				write(1, " ", 1);
	}
}

static	int		check_zwp_begin(char **res_str, t_qual *qual)
{
	int		size;
	int		precision;

	precision = QPR;
	if (QH && ft_strcmp(*res_str, "0") != 0)
		*res_str = ft_strjoin("0", *res_str);
	size = ft_strcmp(*res_str, "0") == 0 ? 0 : (int)ft_strlen(*res_str);
	if (QW > 0 && ft_strcmp(*res_str, "0") == 0 && QPR == -1)
		size++;
	if (!QM)
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
	int		lenght;

	res_str = check_modifier(numb, 2, qual);
	size = check_zwp_begin(&res_str, qual);
	if (ft_strcmp(res_str, "0") == 0 && QPR == 0 && !QH)
	{
		free(res_str);
		return (QW == -1 ? 0 : QW);
	}
	else if (ft_strcmp(res_str, "0") == 0 && QPR == 0 && QH)
	{
		write(1, "0", 1);
		free(res_str);
		return (QW == -1 ? 1 : QW);
	}
	if ((ft_strcmp(res_str, "0") == 0 && QPR == -1) || ft_strcmp(res_str, "0") != 0)
		ft_putstr(res_str);
	lenght = ft_strlen(res_str);
	if (QM == 1)
		binary_check_width(qual, size);
	free(res_str);
	return (lenght == 0 && QW == -1 && QPR != -1 ? 0 :
	ft_max(3, QW, QPR, lenght));
}
