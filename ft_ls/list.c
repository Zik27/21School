/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:33:28 by vurrigon          #+#    #+#             */
/*   Updated: 2019/03/18 13:05:21 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**fill_list(t_dir *list, char *fname, t_dir *subdir, int type)
{
	struct stat	status;
	char		**mtime;

	lstat(fname, &status);
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
	return (mtime);
}

t_dir		*ft_create_file(char *fname, t_dir *subdir, int type)
{
	t_dir		*list;
	int			i;
	char		**mtime;

	list = malloc(sizeof(t_dir));
	if (list)
	{
		mtime = fill_list(list, fname, subdir, type);
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
		else if (type == DT_SOCK)
			current->next_file = ft_create_file(fname, NULL, FT_SOCK);
	}
}
