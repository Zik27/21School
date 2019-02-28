/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:21:58 by djast             #+#    #+#             */
/*   Updated: 2019/02/28 17:33:29 by vurrigon         ###   ########.fr       */
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
		if (*flags[i] == '-')
		{
			++flags[i];
			if (!(fill_flags(&(flags[i]), ls)))
				return (-1);
		}
		else if (opendir(flags[i]) == NULL)
			ft_printf("ft_ls: %s: No such file or directory\n", flags[i]);
		else
			ls->is_dir = 1;
	}
	return (0);
}