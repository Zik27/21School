/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:11 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 19:19:47 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sort_list(t_ls *ls, t_dir **file_list, char *start_path)
{
	if (!ls->not_sort)
	{
		ls->is_sort_by_time ? list_sort_by_time(&((*file_list)->next_file))
		: list_sort_by_name(&((*file_list)->next_file));
		ls->is_sort_by_size ? list_sort_by_size(&((*file_list)->next_file))
		: NULL;
		ls->is_reversed ? list_reverse(&((*file_list)->next_file)) : NULL;
	}
	ls->long_format == 0 ? print_dir(ls, (*file_list)->next_file) :
	print_long(ls, (*file_list)->next_file);
	ls->is_recursive == 1 ? find_subdirs(ls, &(*file_list)->next_file,
		start_path) : NULL;
}

static DIR	*print_open_dir(const char *bpath, t_ls *ls, t_dir **file_list,
						char *start_path)
{
	DIR				*dir;

	if (!(dir = opendir(bpath)))
		return (0);
	if (ls->multiple_files == 1 && ls->first_time == 1)
		(void)ft_printf("%s:\n", (*file_list)->path_file);
	else if ((ft_strcmp((*file_list)->path_file, start_path) != 0 ||
			(ls->multiple_files == 1 && ls->first_time == 0)))
		(void)ft_printf("\n%s:\n", (*file_list)->path_file);
	ls->first_time = 0;
	return (dir);
}

static void	add_in_list(const char *bpath, t_ls *ls, t_dir **file_list,
						char *start_path)
{
	DIR				*dir;
	char			*path;
	struct dirent	*d;
	int				flag;

	dir = print_open_dir(bpath, ls, file_list, start_path);
	flag = 0;
	while ((d = readdir(dir)))
	{
		if (ft_strncmp(d->d_name, ".", 1) == 0 &&
			!ls->is_with_dot && !ls->is_almost_all)
			continue ;
		if ((!ft_strcmp(d->d_name, ".") || !ft_strcmp(d->d_name, "..")) &&
			ls->is_almost_all && !ls->is_with_dot)
			continue ;
		path = generate_name(file_list, d);
		list_push_back(file_list, path, d->d_type);
		flag = 1;
	}
	closedir(dir);
	flag == 1 ? sort_list(ls, file_list, start_path) : NULL;
	delete_branch(file_list);
}

void		find_subdirs(t_ls *ls, t_dir **begin_list, char *start_path)
{
	t_dir *current;

	current = *begin_list;
	while (current != NULL)
	{
		if (current->type == FT_DIR && ft_strncmp((current->path_file +
				((int)ft_strlen(current->path_file) - 2)), "..", 2) != 0)
		{
			if (ft_strncmp((current->path_file +
				((int)ft_strlen(current->path_file) - 2)), "/.", 2) != 0)
			{
				current->subdir = ft_create_file(ft_strdup(current->path_file),
													NULL, FT_ROOT);
				add_in_list(current->path_file, ls, &(current->subdir),
								start_path);
			}
		}
		current = current->next_file;
	}
}

int			prepare_output(t_ls *ls)
{
	int			i;
	t_dir		*file_list;

	i = 0;
	while (ls->path[i])
	{
		if (ft_strcmp(ls->path[i], "") == 0)
		{
			i++;
			continue ;
		}
		file_list = ft_create_file(ft_strdup(ls->path[i]), NULL, FT_ROOT);
		add_in_list(ls->path[i], ls, &file_list, ls->path[i]);
		i++;
	}
	return (1);
}
