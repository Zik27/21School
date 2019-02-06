/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:31:01 by djast             #+#    #+#             */
/*   Updated: 2019/02/06 19:59:58 by vurrigon         ###   ########.fr       */
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
	t_qual *qual;

	qual = (t_qual *)malloc(sizeof(t_qual));
	ft_init_qual(&qual);
	str = ft_check_flags(str, &qual);
	str = ft_check_width(str, &qual, args);
	str = ft_check_precision(str, &qual, args);
	str = ft_check_lenght(str, &qual);
	if (*(str + 1) == 'c' && ft_strcmp(qual->lenght, "l") != 0)
		*printed += ft_c(va_arg(*args, intmax_t), qual);	
	else if (*(str + 1) == 'C' || (*(str + 1) == 'c' && ft_strcmp(qual->lenght, "l") == 0))
		*printed += ft_wc(va_arg(*args, wint_t), qual);
	else if (*(str + 1) == 'O')
	{
		qual->lenght = *(str + 1) == 'O' ? "l" : qual->lenght;
		*printed += ft_o(va_arg(*args, intmax_t), qual);
	}
	else if (*(str + 1) == 'D')
	{
		qual->lenght = *(str + 1) == 'D' ? "l" : qual->lenght;
		*printed += ft_d(va_arg(*args, intmax_t), qual);
	}
	else if (*(str + 1) == 's' && ft_strcmp(qual->lenght, "l") != 0)
		*printed += ft_s(va_arg(*args, char *), qual);
	else if (*(str + 1) == 'S' || (*(str + 1) == 's' && ft_strcmp(qual->lenght, "l") == 0))
		*printed += ft_ws(va_arg(*args, wchar_t *), qual);
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		*printed += ft_d(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'u' || *(str + 1) == 'U')
	{
		qual->lenght = *(str + 1) == 'U' ? "l" : qual->lenght;
		*printed += ft_u(va_arg(*args, uintmax_t), qual);
	}
	else if (*(str + 1) == 'p')
		*printed += ft_p(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'f' && (ft_strcmp(qual->lenght, "") == 0 ||
	ft_strcmp(qual->lenght, "l") == 0))
		*printed += ft_f(va_arg(*args, double), qual);
	else if (*(str + 1) == 'f' && ft_strcmp(qual->lenght, "L") == 0)
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
		if (qual->width > 0 && qual->precision == -1 && !qual->zero)
		{
			*printed += qual->width - 1;
			while (qual->width-- > 1)
				write(1, " ", 1);
		}
		free(qual);
		return (str);
	}
	  //printf("\nQUAL:\nMinus: %d\nPlus: %d\nSpace: %d\nHash: %d\nZero: %d\nWidth: %d\nPrecision: %d\nLenght: %s\nSign: %d\nUint: %d\n",
      //    qual->minus, qual->plus, qual->space, qual->hash, qual->zero, qual->width, qual->precision, qual->lenght, qual->sign, qual->unsint);
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

int main()
{
	int a, b;

	a = printf("42%-30.2x42\n", 0);
	b = ft_printf("42%-30.2x42\n", 0);

	// a = printf("%#X\n", 42);
	// b = ft_printf("%#X\n", 42);

	printf("result = %d %d\n", a, b);
}
