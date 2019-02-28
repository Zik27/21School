/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:03:39 by djast             #+#    #+#             */
/*   Updated: 2019/02/08 20:53:29 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		octal_check_width(t_qual *qual, int size)
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
	int		is_null;

	is_null = ft_strcmp(*res_str, "0") == 0 ? 1 : 0;
	precision = QPR;
	if (QH && !is_null)
		*res_str = ft_strjoin("0", *res_str);
	size = is_null ? 0 : (int)ft_strlen(*res_str);
	if (QW > 0 && is_null && QPR == -1)
		size++;
	if (!QM)
		octal_check_width(qual, size);
	if (precision > size)
		while (precision-- - size > 0)
			write(1, "0", 1);
	return (size);
}

int				ft_o(intmax_t numb, t_qual *qual)
{
	char	*res_str;
	int		size;
	int		l;
	int		is_null;

	res_str = check_modifier(numb, 8, qual);
	size = check_zwp_begin(&res_str, qual);
	is_null = ft_strcmp(res_str, "0") == 0 ? 1 : 0;
	if (is_null && QPR == 0 && !QH)
	{
		free(res_str);
		return (QW == -1 ? 0 : QW);
	}
	else if (is_null && QPR == 0 && QH)
	{
		write(1, "0", 1);
		free(res_str);
		return (QW == -1 ? 1 : QW);
	}
	ft_putstr((is_null && QPR == -1) || !is_null ? res_str : NULL);
	l = ft_strlen(res_str);
	if (QM == 1)
		octal_check_width(qual, size);
	free(res_str);
	return (l == 0 && QW == -1 && QPR != -1 ? 0 : ft_max(3, QW, QPR, l));
}
