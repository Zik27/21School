/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:52:44 by djast             #+#    #+#             */
/*   Updated: 2019/02/08 20:54:16 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				size_fract(char *s)
{
	int count;

	count = 0;
	while (*s)
	{
		count++;
		s++;
	}
	s--;
	while (*s == '0')
	{
		count--;
		s--;
	}
	return (count - 1);
}

int				ft_int_size(char *ans)
{
	int count;

	count = 0;
	while (*ans != '.' && *ans != '\0')
	{
		ans++;
		count++;
	}
	return (count);
}

int				ft_fract_size(char *ans)
{
	int count;

	count = 0;
	while (*ans != '.')
		ans++;
	while (*ans++)
		count++;
	return (count);
}

char			*round_fract(char *ans)
{
	int		count;
	char	*start;

	start = ans;
	count = 0;
	while (*ans++)
	{
		count++;
	}
	ans = ans - 2;
	if (*ans >= '5')
	{
		while (*(ans - 1) == '9')
		{
			*(ans - 1) = '0';
			ans--;
		}
		*(ans - 1) = *(ans - 1) + 1;
	}
	return (ft_strsub(start, 0, count - 1));
}

char			*translate_to_int(char *s, char *ans)
{
	char *digit;
	char *tmp;

	digit = ft_strnew(2);
	while ((*s - 48) * 8 + (*(s + 1) - 48) * 4 + (*(s + 2) - 48)
		* 2 + (*(s + 3) - 48) == 0)
		s = s + 4;
	while (*s)
	{
		*digit = (char)((*s - 48) * 8 + (*(s + 1) - 48) * 4 + (*(s + 2) - 48)
			* 2 + (*(s + 3) - 48) + 48);
		tmp = ans;
		ans = ft_strjoin(ans, digit);
		free(tmp);
		s = s + 4;
	}
	free(digit);
	return (ans);
}
