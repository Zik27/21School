/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:50:19 by djast             #+#    #+#             */
/*   Updated: 2019/02/11 11:44:36 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*get_fract(char *fract, char *ans)
{
	char	*s;
	int		count;
	char	*tmp;

	count = ft_strlen(fract) - 1;
	if (count == -1)
	{
		tmp = ans;
		ans = ft_strjoin(ans, "0");
		free(tmp);
		return (ans);
	}
	s = ft_strnew(DD_SIZE);
	ft_memset(s, '0', DD_SIZE);
	while (count-- >= 0)
	{
		s = shift_right(s);
		push_fract(s, fract);
		fract = shift_right(fract);
		check_sub(s, 0);
	}
	ans = translate_to_int(s, ans, 1);
	free(s);
	return (ans);
}

int				check_sub(char *s, int flag)
{
	if (*s == 0)
		return (flag);
	if ((*s - 48) * 8 + (*(s + 1) - 48) * 4 + (*(s + 2) - 48) * 2
		+ (*(s + 3) - 48) > 7)
	{
		s = sub_one(s);
		return (check_sub(s + 4, 1));
	}
	return (check_sub(s + 4, flag));
}

void			push_fract(char *s, char *c)
{
	while (*c)
		c++;
	c--;
	*s = *c;
}

char			*sub_one(char *s)
{
	int ans;
	int count;
	int copy_ans;

	count = 3;
	ans = (*s - 48) * 8 + (*(s + 1) - 48) * 4 + (*(s + 2) - 48) * 2
	+ (*(s + 3) - 48) - 3;
	copy_ans = ans;
	while (count--)
		s++;
	while (ans != 0)
	{
		*s = ans % 2 == 0 ? '0' : '1';
		ans /= 2;
		s--;
	}
	if (copy_ans < 8 && *s == '1')
		*s = '0';
	if (copy_ans >= 8)
		s++;
	return (s);
}

char			*shift_right(char *fract)
{
	char *start_str;

	start_str = fract;
	while (*fract)
		fract++;
	fract--;
	while (fract != start_str)
	{
		*fract = *(fract - 1);
		fract--;
	}
	*start_str = '0';
	return (start_str);
}
