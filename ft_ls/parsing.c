/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:21:58 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 19:06:24 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			fill_flags2(const char **str, t_ls *ls)
{
	if (**str == 'f')
	{
		ls->not_sort = 1;
		ls->is_with_dot = 1;
	}
	else if (**str == 'n')
	{
		ls->is_numb_gr_user = 1;
		ls->long_format = 1;
	}
	else if (**str == 'S')
		ls->is_sort_by_size = 1;
	else if (**str == 'A')
		ls->is_almost_all = 1;
	else if (**str == 'G')
		ls->colors = 1;
}

static int			fill_flags(const char **str, t_ls *ls)
{
	int flag;

	flag = 0;
	while (**str == 'r' || **str == 'R' || **str == 'l' || **str == 'a' ||
			**str == 't' || **str == 'f' || **str == 'S' || **str == 'A' ||
			**str == 'n' || **str == 'G')
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
		else
			fill_flags2(str, ls);
		flag = 1;
		(*str)++;
	}
	if (**str != '\0')
		return (-**str);
	return (flag);
}

int					parsing_dirs(char const **str, t_ls *ls, int index)
{
	int count;
	int i;
	int size;

	i = index;
	count = 0;
	size = 0;
	while (str[size])
		size++;
	size = size - index > 0 ?
			size - index : 1;
	ls->path = (char **)malloc(sizeof(char *) * (size + 1));
	while (str[i])
		ls->path[count++] = (char *)str[i++];
	ls->path[count] = NULL;
	if (count == 0)
	{
		ls->path[0] = ".";
		ls->path[1] = NULL;
	}
	ls->multiple_files = count > 1 ? 1 : 0;
	return (count > 0 ? 1 : 0);
}

void				check_dirs(t_ls *ls)
{
	int	i;
	DIR	*dir;

	i = 0;
	while (ls->path[i])
	{
		if (!(dir = opendir(ls->path[i])))
		{
			ft_printf("ft_ls: %s: No such file or directory\n",
				ls->path[i]);
			ls->path[i] = "";
		}
		else
			closedir(dir);
		i++;
	}
}

int					parsing_flags(int argc, char const **flags, t_ls *ls)
{
	int i;
	int res;

	i = 0;
	while (i++ < argc - 1)
	{
		if (*flags[i] == '-')
		{
			if (*(flags[i] + 1) == '\0')
				break ;
			++flags[i];
			if ((res = fill_flags(&(flags[i]), ls)) < 0)
				return (res);
		}
		else
			break ;
	}
	parsing_dirs(flags, ls, i);
	check_dirs(ls);
	return (0);
}
