/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:31:01 by djast             #+#    #+#             */
/*   Updated: 2019/01/25 14:00:06 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_c(char str)
{
	write(1, &str, 1);
}

void ft_s(char *str)
{
	write(1, str, ft_strlen(str));
}

void ft_p(long long addr)
{
    char *result;
    result = ft_translation(addr, 16);
    write(1, "0x", 2);
    ft_putstr(result);
}

void ft_d(intmax_t d, t_qual *qual)
{
	if (ft_strcmp(qual->lenght, "ll") == 0)
		ft_putllnbr((long long int)d);
	else if (ft_strcmp(qual->lenght, "l") == 0)
		ft_putllnbr((long int)d);
	else if (ft_strcmp(qual->lenght, "h") == 0)
		ft_putllnbr((short int)d);
	else if (ft_strcmp(qual->lenght, "hh") == 0)
		ft_putllnbr((signed char)d);
	else
		ft_putllnbr((int)d);
}


void ft_u(uintmax_t d, t_qual *qual)
{
	if (ft_strcmp(qual->lenght, "ll") == 0)
		ft_putllunbr((unsigned long long int)d);
	else if (ft_strcmp(qual->lenght, "l") == 0)
		ft_putllunbr((unsigned long int)d);
	else if (ft_strcmp(qual->lenght, "h") == 0)
		ft_putllunbr((unsigned short int)d);
	else if (ft_strcmp(qual->lenght, "hh") == 0)
		ft_putllunbr((unsigned char)d);
	else
		ft_putllunbr((unsigned int)d);
}

void ft_f(long double d, t_qual *qual)
{
	intmax_t first;
	long double last;
	int i;

	i = 0;
	first = d / 1;
	last = d - (int)d;
	//printf("%Lf\n", last);
	if (ft_strcmp(qual->lenght, "l") == 0 || ft_strcmp(qual->lenght, "") == 0)
	{
		ft_putllunbr(first);
		write(1, ".", 1);
		while(i++ != 6)
		{
			ft_putllnbr((last * 10 - (int)last));
			last = last * 10 - (int)(last * 10);
		}
	}
	else if (ft_strcmp(qual->lenght, "L") == 0)
	{
		ft_putllunbr(first);
		write(1, ".", 1);
		while(i++ != 6)
		{
			ft_putllnbr((last * 10 - (int)last));
			last = last * 10 - (int)(last * 10);
		}
	}
}

void ft_o(intmax_t numb)
{
	char *result_str;

	result_str = ft_translation(numb, 8);
	ft_putstr(result_str);
}

void ft_x(intmax_t numb, int flag)
{
	char *result_str;

	result_str = ft_translation(numb, 16);
	if (flag)
		ft_upper_str(result_str);
	ft_putstr(result_str);
}



char *ft_check_lenght(char *str, t_qual **qual)
{
	if (*(str + 1) == 'l' && *(str + 2) == 'l')
	{
		(*qual)->lenght = "ll";
		return(str + 2);
	}
	else if (*(str + 1) == 'l')
	{
		(*qual)->lenght = "l";
		return (str + 1);
	}
	else if (*(str + 1) == 'h' && *(str + 2) == 'h')
	{
		(*qual)->lenght = "hh";
		return (str + 2);
	}
	else if (*(str + 1) == 'h')
	{
		(*qual)->lenght = "h";
		return (str + 1);
	}
	else if (*(str + 1) == 'L')
	{
		(*qual)->lenght = "L";
		return (str + 1);
	}
	else
		(*qual)->lenght = "";
	return (str);
}

char *ft_check_flags(char *str, t_qual **qual)
{
	if (*(str + 1) == '-' || *(str + 1) == '+' || *(str + 1) == ' ' || *(str + 1) == '#' || *(str + 1) == '0')
	{
		if (*(str + 1) == '-')
			(*qual)->minus = 1;
		else if(*(str + 1) == '+')
			(*qual)->plus = 1;
		else if(*(str + 1) == ' ')
			(*qual)->space = 1;
		else if(*(str + 1) == '#')
			(*qual)->hash = 1;
		else if(*(str + 1) == '0')
			(*qual)->zero = 1;
		return (ft_check_flags(str + 1, qual));
	}
	return (str);
}

char *ft_check_width(char *str, t_qual **qual, va_list *args)
{
	int width;

	width = 0;
	if(*(str + 1) == '*')
		(*qual)->width = va_arg(*args, int);
	else
	{
		while (ft_isdigit(*(str + 1)))
			width = width * 10 + (*(str++ + 1) - 48);
		(*qual)->width = width;
	}
	return(str);
}

char *ft_check_precision(char *str, t_qual **qual, va_list *args)
{
	int precision;

	precision = 0;
	if(*(str + 1) == '.')
	{
		if(*(str + 2) == '*')
		{
			(*qual)->precision = va_arg(*args, int);
			return (str + 2);
		}
		else
		{
			while (ft_isdigit(*(str + 2)))
				precision = precision * 10 + (*(str++ + 2) - 48);
		}
	}
	(*qual)->precision = precision;
	return (str + 1);
}

char *ft_check_percent(char *str, va_list *args)
{
	t_qual *qual;

	qual = (t_qual *) malloc (sizeof(t_qual));

	str = ft_check_flags(str, &qual);
	str = ft_check_width(str, &qual, args);
	str = ft_check_precision(str, &qual, args);
	str = ft_check_lenght(str, &qual);
	printf("\nQUAL:\nMinus: %d\nPlus: %d\nSpace: %d\nHash: %d\nZero: %d\nWidth: %d\nPrecision: %d\nLenght: %s\n",
		qual->minus, qual->plus, qual->space, qual->hash, qual->zero, qual->width, qual->precision, qual->lenght);
	if (*(str + 1) == 'c')
		ft_c(va_arg(*args, intmax_t));
	else if (*(str + 1) == 's')
		ft_s(va_arg(*args, char *));
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		ft_d(va_arg(*args, intmax_t), qual);
	else if (*(str + 1) == 'u')
		ft_u(va_arg(*args, uintmax_t), qual);
	else if (*(str + 1) == 'p')
        ft_p(va_arg(*args, intmax_t));
    else if (*(str + 1) == 'f' && (ft_strcmp(qual->lenght, "") == 0 || ft_strcmp(qual->lenght, "l") == 0))
        ft_f(va_arg(*args, 	double), qual);
    else if (*(str + 1) == 'f' && ft_strcmp(qual->lenght, "L") == 0)
        ft_f(va_arg(*args, 	long double), qual);
    else if (*(str + 1) == '%')
    	write(1, "%", 1);
    else if (*(str + 1) == 'o')
    	ft_o(va_arg(*args, intmax_t));
    else if (*(str + 1) == 'x')
    	ft_x(va_arg(*args, intmax_t), 0);
    else if (*(str + 1) == 'X')
    	ft_x(va_arg(*args, intmax_t), 1);
	else
	{
		free(qual);
		return (str);
	}
	free(qual);
	return (str + 1);
}

int ft_parse_str(char *format, va_list *argptr)
{
	char *percent;

	percent = ft_strchr(format, '%');
	if (percent == NULL)
	{
		ft_putstr(format);
		return (strlen(format));	
	}
	else
	{
		while (format != percent)
		{
			ft_putchar(*format);
			format++;
		}
		format = ft_check_percent(format, argptr);
		return(ft_parse_str(format + 1, argptr));
	}
	return (0);
}

int ft_printf(const char *format, ...)
{
	va_list argptr;

	va_start(argptr, format);
	ft_parse_str((char *)format, &argptr);
	va_end(argptr);
	return (0);
}

int main()
{
	int d = -32;
	//printf("%s\n", a);
	//c = c % 10.0;
    //printf("werwfgekjhf %.1s\n", d);
	ft_printf("%12.10ld\n", d);
	printf("%12.10d", d);
	return 0;
}
