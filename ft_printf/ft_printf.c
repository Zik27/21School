/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:31:01 by djast             #+#    #+#             */
/*   Updated: 2019/02/07 20:25:01 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_init_qual(t_qual **qual)
{
	(*qual)->minus = 0;
	(*qual)->plus = 0;
	(*qual)->space = 0;
	(*qual)->hash = 0;
	(*qual)->zero = 0;
	(*qual)->width = -1;
	(*qual)->precision = -1;
	(*qual)->lenght = "";
	(*qual)->sign = -1;
	(*qual)->unsint = 0;
}

char		*ft_check_percent(char *str, va_list *args, int *printed)
{
	t_qual	*qual;

	qual = (t_qual *)malloc(sizeof(t_qual));
	ft_init_qual(&qual);
	str = ft_check_flags(str, &qual);
	str = ft_check_width(str, &qual, args);
	str = ft_check_precision(str, &qual, args);
	str = ft_check_lenght(str, &qual);
	if (*(str + 1) == 'c' && ft_strcmp(QL, "l") != 0)
		*printed += ft_c(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'C' || (*(str + 1) == 'c' && ft_strcmp(QL, "l") == 0))
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
	else if (*(str + 1) == 'S' || (*(str + 1) == 's' && ft_strcmp(QL, "l") == 0))
		*printed += ft_ws(va_arg(*args, wchar_t *), qual);
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		*printed += ft_d(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'u' || *(str + 1) == 'U')
	{
		QL = *(str + 1) == 'U' ? "l" : QL;
		*printed += ft_u(va_arg(*args, uintmax_t), qual);
	}
	else if (*(str + 1) == 'p')
		*printed += ft_p(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'f' && (ft_strcmp(QL, "") == 0 ||
	ft_strcmp(QL, "l") == 0))
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
	{
		if (QW > 0 && QPR == -1 && !QZ)
		{
			*printed += QW - 1;
			while (QW-- > 1)
				write(1, " ", 1);
		}
		free(qual);
		return (str);
	}
	//printf("\nQUAL:\nMinus: %d\nPlus: %d\nSpace: %d\nHash: %d\nZero: %d\nWidth: %d\nPrecision: %d\nLenght: %s\nSign: %d\nUint: %d\n",
	//QM, QPL, QSP, QH, QZ, QW, QPR, QL, QSN, QUS);
	free(qual);
	return (str + 1);
}

int			ft_parse_str(char *format, va_list *argptr, int *printed)
{
	char *percent;

	percent = ft_strchr(format, '%');
	if (percent == NULL)
	{
		ft_putstr(format);
		return (ft_strlen(format) + (*printed));
	}
	else
	{
		while (format != percent)
		{
			(*printed)++;
			ft_putchar(*format);
			format++;
		}
		format = ft_check_percent(format, argptr, printed);
		return (ft_parse_str(format + 1, argptr, printed));
	}
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list	argptr;
	int		printed;

	printed = 0;
	va_start(argptr, format);
	printed = ft_parse_str((char *)format, &argptr, &printed);
	va_end(argptr);
	return (printed);
}

// int main()
// {
// 	int a, b;

// 	a = printf("%+lld\n", -488612772);
// 	b = ft_printf("%+lld\n", -488612772);
// 	printf("result = %d %d\n", a, b);

// 	a = printf("%+.2d\n", -488612772);
// 	b = ft_printf("%+.2d\n", -488612772);
// 	printf("result = %d %d\n", a, b);

// 	a = printf("%+.16d\n", -1403635508);
// 	b = ft_printf("%+.16d\n", -1403635508);
// 	printf("result = %d %d\n", a, b);

// 	a = printf("%+42.23d\n", 464641808);
// 	b = ft_printf("%+42.23d\n", 464641808);
// 	printf("result = %d %d\n", a, b);

// 	a = printf("% .41d\n", 1496275204);
// 	b = ft_printf("% .41d\n", 1496275204);
// 	printf("result = %d %d\n", a, b);

// 	a = printf("%0+52.2lld\n", 0);
// 	b = ft_printf("%0+52.2lld\n", 0);
// 	printf("result = %d %d\n", a, b);
// 	// a = printf("\\!/%+026.2hd\\!/\n", -1537181505);
// 	// b = ft_printf("\\!/%+026.2hd\\!/\n", -1537181505);
// 	// printf("result = %d %d\n", a, b);
// 	// a = printf("% 18.12jd\n", -25138743);
// 	// b = ft_printf("% 18.12jd\n", -25138743);
// 	// printf("result = %d %d\n", a, b);
// 	// a = printf("%+-59d\n", 1820675911);
// 	// b = ft_printf("%+-59d\n", 1820675911);
// 	// printf("result = %d %d\n", a, b);
// }
