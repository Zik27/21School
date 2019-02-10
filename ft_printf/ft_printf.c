/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:31:01 by djast             #+#    #+#             */
/*   Updated: 2019/02/10 16:37:09 by vurrigon         ###   ########.fr       */
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
	if (ft_isdigit(*(str + 1)))
	{
		QW = *(str + 1) - 48;
		str++;
	}
	if (!ft_check_alpha1(str, args, printed, qual))
		if (!ft_check_alpha2(str, args, printed, qual))
		{
			str = ft_qual_no_found(str, printed, qual);
			return (str);
		}
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
