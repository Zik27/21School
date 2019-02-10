/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:04:04 by djast             #+#    #+#             */
/*   Updated: 2019/02/08 18:54:51 by vurrigon         ###   ########.fr       */
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

static void		check_width_begin(char *result_str, int lenght,
					int len_nbr, t_qual *qual)
{
	int tmp;
	int	is_null;

	is_null = ft_strcmp(result_str, "0") == 0 ? 1 : 0;
	if (QPR > 0 && len_nbr < QPR &&
	(!QH || is_null))
		tmp = QW - QPR;
	else if (QPR > 0 && len_nbr < QPR &&
	QH && !is_null)
		tmp = QW - QPR - 2;
	else if (is_null && QPR == 0)
		tmp = QW;
	else
		tmp = QW - lenght;
	if (QZ && QPR == -1)
		while (tmp-- > 0)
			write(1, "0", 1);
	else
		while (tmp-- > 0)
			write(1, " ", 1);
}

static int		check_minus_making_retv(char *result_str, int lenght,
					int len_nbr, t_qual *qual)
{
	int value_ret;
	int tmp;

	if (QM && QPR < QW)
	{
		tmp = QW;
		while (tmp-- - lenght > 0)
			write(1, " ", 1);
	}
	value_ret = ft_max(2, QPR, len_nbr);
	if (QH && ft_strcmp(result_str, "0") != 0)
		value_ret += 2;
	return (value_ret);
}

static int		length_detect(char *result_str, int len_nbr,
					int flag, t_qual *qual)
{
	int lenght;
	int	is_null;

	is_null = ft_strcmp(result_str, "0") == 0 ? 1 : 0;
	if (QH && !is_null && QZ && QPR == -1)
		write(1, flag ? "0X" : "0x", 2);
	if (QH && !is_null && (QPR == -1 || QPR <= len_nbr))
		lenght = len_nbr + 2;
	else if (QH && !is_null && QPR > len_nbr)
		lenght = QPR + 2;
	else if (QPR > 0 && QPR > len_nbr)
		lenght = QPR;
	else
		lenght = len_nbr;
	return (lenght);
}

int				ft_x(intmax_t numb, int flag, t_qual *qual)
{
	char	*result_str;
	int		tmp;
	int		lenght_wide;
	int		lenght_prec;

	result_str = check_modifier(numb, 16, qual);
	lenght_prec = ft_strlen(result_str);
	lenght_wide = length_detect(result_str, lenght_prec, flag, qual);
	if (!QM && QW > 0)
		check_width_begin(result_str, lenght_wide, lenght_prec, qual);
	tmp = QPR;
	if (QH && ft_strcmp(result_str, "0") != 0 && (!QZ || (QPR >= 0 && QZ)))
		write(1, flag ? "0X" : "0x", 2);
	if (tmp > 0)
		while (tmp-- - lenght_prec > 0)
			write(1, "0", 1);
	if (ft_strcmp(result_str, "0") == 0 && QPR == 0)
	{
		free(result_str);
		return (QW > 0 ? QW : 0);
	}
	ft_putstr(flag ? ft_upper_str(result_str) : result_str);
	tmp = check_minus_making_retv(result_str, lenght_wide, lenght_prec, qual);
	free(result_str);
	return (tmp < QW ? QW : tmp);
}
