/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:52:11 by djast             #+#    #+#             */
/*   Updated: 2019/03/14 19:04:27 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*ft_create_file(char *fname, t_dir *subdir, int type)
{
	t_dir		*list;
	struct stat	status;
	char		**mtime;
	int			i;

	lstat(fname, &status);
	list = malloc(sizeof(t_dir));
	if (list)
	{
		list->path_file = fname;
		list->next_file = NULL;
		list->subdir = subdir;
		list->type = type;
		list->rules = status.st_mode;
		list->links = status.st_nlink;
		list->user = status.st_uid;
		list->group = status.st_gid;
		list->size = status.st_size;
		mtime = ft_strsplit(ctime(&status.st_mtime), ' ');
		list->month = ft_strdup(mtime[1]);
		list->day = ft_strdup(mtime[2]);
		list->time = ft_strsub(mtime[3], 0, 5);
		list->mtime = status.st_mtimespec.tv_sec;
		list->mtime_nano = status.st_mtimespec.tv_nsec;
		list->block = status.st_blocks;
		list->extended_attributes = listxattr(list->path_file, NULL, 300, 0);
		i = 0;
		while (i != 5)
			free(mtime[i++]);
		free(mtime);
	}
	return (list);
}

void		list_push_back(t_dir **begin_list, char *fname, unsigned char type)
{
	t_dir		*current;
	struct stat	sb;

	if (*begin_list)
	{
		current = *begin_list;
		while (current->next_file)
			current = current->next_file;
		if (type == DT_DIR)
			current->next_file = ft_create_file(fname, NULL, FT_DIR);
		else if (stat(fname, &sb) == 0 && sb.st_mode & S_IXUSR)
			current->next_file = ft_create_file(fname, NULL, FT_FILE_EXE);
		else if (type == DT_REG)
			current->next_file = ft_create_file(fname, NULL, FT_FILE);
		else if (type == DT_LNK)
			current->next_file = ft_create_file(fname, NULL, FT_LNK);
	}
}

static int	add_in_list(const char *bpath, t_ls *ls, t_dir **file_list,
						char *start_path)
{
	DIR				*dir;
	char			*path;
	struct dirent	*d_entry;
	char			*tmp;
	int				flag;

	flag = 0;
	if (!(dir = opendir(bpath)))
		return (-1);
	if (ls->multiple_files == 1 && ls->first_time == 1)
		(void)ft_printf("%s:\n", (*file_list)->path_file);
	else if ((ft_strcmp((*file_list)->path_file, start_path) != 0 ||
			(ls->multiple_files == 1 && ls->first_time == 0)))
		(void)ft_printf("\n%s:\n", (*file_list)->path_file);
	ls->first_time = 0;
	while ((d_entry = readdir(dir)))
	{
		if (ft_strncmp(d_entry->d_name, ".", 1) == 0 &&
			!ls->is_with_dot && !ls->is_almost_all)
			continue ;
		if ((ft_strcmp(d_entry->d_name, ".") == 0 ||
			ft_strcmp(d_entry->d_name, "..") == 0) &&
			ls->is_almost_all && !ls->is_with_dot)
			continue ;
		path = ft_strjoin((*file_list)->path_file, "/");
		tmp = path;
		path = ft_strjoin(path, d_entry->d_name);
		free(tmp);
		list_push_back(file_list, path, d_entry->d_type);
		flag = 1;
	}
	closedir(dir);

	if (flag == 1)
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
	delete_branch(file_list);
	return (1);
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
		file_list = ft_create_file(ft_strdup(ls->path[i]), NULL, FT_ROOT);
		add_in_list(ls->path[i], ls, &file_list, ls->path[i]);
		i++;
	}
	return (1);
}
