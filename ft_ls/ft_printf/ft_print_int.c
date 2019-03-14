/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:51:34 by djast             #+#    #+#             */
/*   Updated: 2019/02/11 12:20:54 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*get_int(char *decimal, char *ans)
{
	char	*s;
	int		count;

	count = ft_strlen(decimal) - 1;
	s = ft_strnew(DD_SIZE);
	s = ft_memset(s, '0', DD_SIZE);
	while (count-- > 0)
	{
		s = shift_left(s);
		s = push_digit(s, decimal[0]);
		decimal = shift_left(decimal);
		check_sum(s, 0);
	}
	s = shift_left(s);
	s = push_digit(s, decimal[0]);
	ans = translate_to_int(s, ans, 0);
	free(s);
	return (ans);
}

char			*add_one(char *s)
{
	char *start;

	start = s;
	if (*(s + 3) == '1')
	{
		*(s + 3) = '0';
		if (*(s + 2) == '1')
		{
			*(s + 2) = '0';
			if (*(s + 1) == '1')
			{
				*(s + 1) = '0';
				*s = '1';
			}
			else
				*(s + 1) = '1';
		}
		else
			*(s + 2) = '1';
	}
	else
		*(s + 3) = '1';
	return (s);
}

int				check_sum(char *s, int flag)
{
	if (!*s)
		return (flag);
	if ((*s - 48) * 8 + (*(s + 1) - 48) * 4 + (*(s + 2) - 48) * 2
		+ (*(s + 3) - 48) >= 5)
	{
		s = add_one(s);
		s = add_one(s);
		s = add_one(s);
		return (check_sum(s + 4, 1));
	}
	return (check_sum(s + 4, flag));
}

char			*shift_left(char *decimal)
{
	char *start_str;

	start_str = decimal;
	decimal++;
	while (*decimal)
	{
		*(decimal - 1) = *decimal;
		decimal++;
	}
	*(decimal - 1) = 0;
	return (start_str);
}

char			*push_digit(char *s, char c)
{
	int		index;
	char	*start;

	start = s;
	index = DD_SIZE - 1;
	while (index-- != 0)
		s++;
	if (!c)
		*s = '0';
	else
		*s = c;
	return (start);
}
