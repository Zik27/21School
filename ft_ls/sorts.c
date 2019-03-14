/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:14:29 by djast             #+#    #+#             */
/*   Updated: 2019/03/13 18:27:42 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_sort_sw(t_dir **begin_list, t_dir **list_cur,
						t_dir **list_next, t_dir **list_prev)
{
	(*list_cur)->next_file = (*list_cur)->next_file->next_file;
	if (*list_prev)
		(*list_prev)->next_file = *list_next;
	(*list_next)->next_file = *list_cur;
	if (*list_cur == *begin_list)
		*begin_list = *list_next;
}

void	list_is_sort_t(t_dir **begin_list, t_dir *list_cur,
						t_dir *list_prev, int *flag)
{
	t_dir *list_next;

	while (list_cur->next_file)
	{
		list_next = list_cur->next_file;
		if ((list_cur->mtime < list_next->mtime) ||
			(list_cur->mtime == list_next->mtime &&
			list_cur->mtime_nano < list_next->mtime_nano) ||
			(list_cur->mtime == list_next->mtime &&
			list_cur->mtime_nano == list_next->mtime_nano &&
			ft_strcmp(list_cur->path_file, list_next->path_file) > 0))
		{
			*flag = 1;
			list_sort_sw(begin_list, &list_cur, &list_next, &list_prev);
		}
		list_prev = list_cur;
		if (list_cur->next_file)
			list_cur = list_cur->next_file;
	}
}

void	list_sort_by_name(t_dir **begin_list)
{
	t_dir	*list_prev;
	t_dir	*list_cur;
	t_dir	*list_next;
	int		flag;

	list_cur = *begin_list;
	while (1)
	{
		flag = 0;
		list_cur = *begin_list;
		list_prev = NULL;
		while (list_cur->next_file)
		{
			list_next = list_cur->next_file;
			if (ft_strcmp(list_cur->path_file, (list_next->path_file)) > 0)
			{
				flag = 1;
				list_sort_sw(begin_list, &list_cur, &list_next, &list_prev);
			}
			list_prev = list_cur;
			list_cur = list_cur->next_file ? list_cur->next_file : list_cur;
		}
		if (flag == 0)
			break ;
	}
}

void	list_sort_by_time(t_dir **begin_list)
{
	t_dir	*list_cur;
	int		flag;

	list_cur = *begin_list;
	while (1)
	{
		flag = 0;
		list_cur = *begin_list;
		list_is_sort_t(begin_list, list_cur, NULL, &flag);
		if (flag == 0)
			break ;
	}
}

void	list_sort_by_size(t_dir **begin_list)
{
	t_dir	*list_prev;
	t_dir	*list_cur;
	t_dir	*list_next;
	int		flag;

	list_cur = *begin_list;
	while (1)
	{
		flag = 0;
		list_cur = *begin_list;
		list_prev = NULL;
		while (list_cur->next_file)
		{
			list_next = list_cur->next_file;
			if (list_cur->size < list_next->size)
			{
				flag = 1;
				list_sort_sw(begin_list, &list_cur, &list_next, &list_prev);
			}
			list_prev = list_cur;
			list_cur = list_cur->next_file ? list_cur->next_file : list_cur;
		}
		if (flag == 0)
			break ;
	}
}
