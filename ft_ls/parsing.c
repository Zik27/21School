/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:21:58 by djast             #+#    #+#             */
/*   Updated: 2019/03/01 17:06:28 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int fill_flags(const char **str, t_ls *ls)
{
	int flag;

	flag = 0;
	while (**str == 'r' || **str == 'R' || **str == 'l' || **str == 'a' || **str == 't')
	{
		if (**str == 'r')
			ls->is_reversed = 1;
		else if (**str == 'R')
			ls->is_recursive = 1;
		else if (**str == 'l')
			ls->long_format = 1;
		else if (**str == 'a')
			ls->is_with_dot = 1;
		else if (**str == 't')
			ls->is_sort_by_time = 1;
		flag = 1;
		(*str)++;
	}
	if (**str != '\0')
		return (0);
	return (flag);
}

int parsing_flags(int argc, char const **flags, t_ls *ls)
{
	int i;

	i = 0;
	while (i++ < argc - 1)
	{
		ls->path = (char *)flags[i];
		if (*flags[i] == '-')
		{
			++flags[i];
			if (!(fill_flags(&(flags[i]), ls)))
				return (-1);
			ls->path = ".";
		}
		else if (opendir(flags[i]) == NULL)
			return (-2);
		else
		{
			ls->path = (char *)flags[i];
			return (0);
		}
	}
	return (0);
}