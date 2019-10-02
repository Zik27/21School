/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:52:06 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 19:05:07 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_size_array(char **str)
{
	int	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

void			delete_branch(t_dir **file_list)
{
	t_dir *current;
	t_dir *next;

	current = *file_list;
	next = NULL;
	if (current)
		next = (*file_list)->next_file;
	while (next)
	{
		free(current->month);
		free(current->day);
		free(current->time);
		free(current->path_file);
		free(current);
		current = next;
		next = current->next_file;
	}
	free(current->path_file);
	free(current->month);
	free(current->day);
	free(current->time);
	free(current);
	current = NULL;
}

void			list_reverse(t_dir **begin_list)
{
	t_dir	*list_prev;
	t_dir	*list_cur;
	t_dir	*list_next;

	list_next = NULL;
	list_prev = NULL;
	list_cur = *begin_list;
	while (list_cur)
	{
		list_next = list_cur->next_file;
		list_cur->next_file = list_prev;
		list_prev = list_cur;
		list_cur = list_next;
	}
	*begin_list = list_prev;
}

long long		ft_total(t_dir *file_list)
{
	t_dir		*current;
	long long	total;

	total = 0;
	current = file_list;
	while (current)
	{
		total += current->block;
		current = current->next_file;
	}
	return (total);
}

void			print_dir(t_ls *ls, t_dir *file_list)
{
	t_dir *current;

	current = file_list;
	while (current)
	{
		if (ls->colors == 1)
		{
			if (current->type == FT_FILE_EXE)
				ft_printf(RED_DARK"%s\n"RESET, ft_strrchr(
					current->path_file, '/') + 1);
			else if (current->type == FT_DIR)
				ft_printf(CYAN"%s\n"RESET, ft_strrchr(
					current->path_file, '/') + 1);
			else if (current->type == FT_LNK)
				ft_printf(MAGENTA_DARK"%s\n"RESET, ft_strrchr(
					current->path_file, '/') + 1);
			else
				ft_printf("%s\n", ft_strrchr(current->path_file, '/') + 1);
		}
		else
			ft_printf("%s\n", ft_strrchr(current->path_file, '/') + 1);
		current = current->next_file;
	}
}
