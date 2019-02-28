/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:59:18 by djast             #+#    #+#             */
/*   Updated: 2019/02/10 16:19:05 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_alpha1(char *str, va_list *args, int *printed, t_qual *qual)
{
	if (*(str + 1) == 'c' && ft_strcmp(QL, "l") != 0)
		*printed += ft_c(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'C' || (*(str + 1) == 'c' &&
		ft_strcmp(QL, "l") == 0))
		*printed += ft_wc(va_arg(*args, wint_t), qual);
	else if (*(str + 1) == 'O')
	{
		QL = *(str + 1) == 'O' ? "l" : QL;
		*printed += ft_o(va_arg(*args, intmax_t), qual);
	}
	else if (*(str + 1) == 'D')
	{
		QL = *(str + 1) == 'D' ? "l" : QL;
		*printed += ft_d(va_arg(*args, intmax_t), qual);
	}
	else if (*(str + 1) == 's' && ft_strcmp(QL, "l") != 0)
		*printed += ft_s(va_arg(*args, char *), qual);
	else if (*(str + 1) == 'S' || (*(str + 1) == 's' &&
		ft_strcmp(QL, "l") == 0))
		*printed += ft_ws(va_arg(*args, wchar_t *), qual);
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		*printed += ft_d(va_arg(*args, intmax_t), qual);
	else
		return (0);
	return (1);
}

int		ft_check_alpha2(char *str, va_list *args, int *printed, t_qual *qual)
{
	if (*(str + 1) == 'u' || *(str + 1) == 'U')
	{
		QL = *(str + 1) == 'U' ? "l" : QL;
		*printed += ft_u(va_arg(*args, uintmax_t), qual);
	}
	else if (*(str + 1) == 'p')
		*printed += ft_p(va_arg(*args, intmax_t), qual);
	else if ((*(str + 1) == 'f' && (ft_strcmp(QL, "") == 0 ||
	ft_strcmp(QL, "l") == 0)) || *(str + 1) == 'F')
		*printed += ft_f(va_arg(*args, double), qual);
	else if (*(str + 1) == 'f' && ft_strcmp(QL, "L") == 0)
		*printed += ft_f(va_arg(*args, long double), qual);
	else if (*(str + 1) == '%')
		*printed += ft_percent('%', qual);
	else if (*(str + 1) == 'o')
		*printed += ft_o(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'x')
		*printed += ft_x(va_arg(*args, intmax_t), 0, qual);
	else if (*(str + 1) == 'X')
		*printed += ft_x(va_arg(*args, intmax_t), 1, qual);
	else if (*(str + 1) == 'b')
		*printed += ft_b(va_arg(*args, intmax_t), qual);
	else
		return (0);
	return (1);
}

char	*ft_qual_no_found(char *str, int *printed, t_qual *qual)
{
	if (QW > 0)
		*printed += QW - 1;
	if (QW > 0 && !QZ && !QM)
		while (QW-- > 1)
			write(1, " ", 1);
	else if (QW > 0 && QZ && !QM)
		while (QW-- > 1)
			write(1, "0", 1);
	if (!*(str + 1))
	{
		free(qual);
		return (str);
	}
	write(1, (str + 1), 1);
	*printed += 1;
	if (QW > 0 && QPR == -1 && QM)
		while (QW-- > 1)
			write(1, " ", 1);
	free(qual);
	return (str + 1);
}
