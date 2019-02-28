/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:04:55 by djast             #+#    #+#             */
/*   Updated: 2019/02/11 10:14:53 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_check_lenght(char *str, t_qual **qual)
{
	if (*(str + 1) == 'l' && *(str + 2) == 'l')
	{
		(*qual)->lenght = "ll";
		return (str + 2);
	}
	else if (*(str + 1) == 'h' && *(str + 2) == 'h')
	{
		(*qual)->lenght = "hh";
		return (str + 2);
	}
	else if (*(str + 1) == 'l' || *(str + 1) == 'h' ||
	*(str + 1) == 'L' || *(str + 1) == 'j' || *(str + 1) == 'z')
	{
		if (*(str + 1) == 'l')
			(*qual)->lenght = "l";
		else if (*(str + 1) == 'h')
			(*qual)->lenght = "h";
		else if (*(str + 1) == 'L')
			(*qual)->lenght = "L";
		else
			(*qual)->lenght = *(str + 1) == 'j' ? "j" : "z";
		return (str + 1);
	}
	return (str);
}

char		*ft_check_flags(char *str, t_qual **qual)
{
	if (*(str + 1) == '-' || *(str + 1) == '+' || *(str + 1) == ' ' ||
		*(str + 1) == '#' || *(str + 1) == '0')
	{
		if (*(str + 1) == '-')
			(*qual)->minus = 1;
		else if (*(str + 1) == '+')
			(*qual)->plus = 1;
		else if (*(str + 1) == ' ')
			(*qual)->space = 1;
		else if (*(str + 1) == '#')
			(*qual)->hash = 1;
		else if (*(str + 1) == '0')
			(*qual)->zero = 1;
		return (ft_check_flags(str + 1, qual));
	}
	return (str);
}

static void	insert_star_width(t_qual **qual, va_list *args)
{
	(*qual)->width = va_arg(*args, int);
	if ((*qual)->width < 0)
	{
		(*qual)->width = -(*qual)->width;
		(*qual)->minus = 1;
	}
}

char		*ft_check_width(char *str, t_qual **qual, va_list *args)
{
	int width;

	width = -1;
	if (*(str + 1) == '*')
		insert_star_width(qual, args);
	else
	{
		while (ft_isdigit(*(str + 1)))
		{
			if (width == -1)
				width = 0;
			width = width * 10 + (*(str++ + 1) - 48);
		}
		(*qual)->width = width;
		if (*(str + 1) != '*')
			return (str);
		else
			(*qual)->width = va_arg(*args, int);
	}
	return (str + 1);
}

char		*ft_check_precision(char *str, t_qual **qual, va_list *args)
{
	int precision;

	precision = -1;
	if (*(str + 1) == '.')
	{
		str++;
		if (*(str + 1) == '*')
		{
			(*qual)->precision = va_arg(*args, int);
			if ((*qual)->precision < 0)
				(*qual)->precision = -1;
			return (str + 1);
		}
		else
		{
			precision = 0;
			while (*(str + 1) == '.')
				str++;
			while (ft_isdigit(*(str + 1)))
				precision = precision * 10 + (*(str++ + 1) - 48);
		}
	}
	(*qual)->precision = precision;
	return (str);
}
