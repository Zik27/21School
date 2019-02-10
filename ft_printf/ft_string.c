/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:02:10 by djast             #+#    #+#             */
/*   Updated: 2019/02/08 18:55:35 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_minus(t_qual *qual, char *str)
{
	int real_width;

	real_width = QW;
	if (QM == 1)
	{
		write(1, str, ft_strlen(str));
		while (real_width-- > (int)ft_strlen(str))
			write(1, " ", 1);
	}
	else
	{
		if (QZ)
			while (real_width-- > (int)ft_strlen(str))
				write(1, "0", 1);
		else
			while (real_width-- > (int)ft_strlen(str))
				write(1, " ", 1);
		write(1, str, ft_strlen(str));
	}
}

int				ft_s(char *str, t_qual *qual)
{
	int real_precision;

	real_precision = QPR;
	if (!str)
		str = "(null)";
	if (real_precision >= 0)
		str = ft_strsub(str, 0, real_precision);
	check_minus(qual, str);
	if ((QW == -1 && QPR > (int)ft_strlen(str))
	|| QW < (int)ft_strlen(str))
		return (ft_strlen(str));
	else if (QW > (int)ft_strlen(str))
		return (QW);
	return (ft_strlen(str) == 0 && QW == -1 &&
	QPR != -1 ? 0 :
	ft_max(2, QW, ft_strlen(str)));
}
