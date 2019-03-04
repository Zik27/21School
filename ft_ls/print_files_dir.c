/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:53:20 by vurrigon          #+#    #+#             */
/*   Updated: 2019/03/01 19:08:40 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void find_subdirs(t_ls *ls, t_dir **begin_list);

void	print_dir(t_ls *ls, t_dir *file_list)
{
	t_dir *current;

	current = file_list;
	while (current)
	{
		ft_printf("%s\n", ft_strrchr(current->path_file, '/') + 1);
		current = current->next_file;
	}
	current = file_list;
	if (ls->is_recursive == 1)
		while (current)
		{
			if (current->type == FT_DIR)
			{
				ft_printf("\n%s:\n", current->subdir->path_file);
				print_dir(ls, current->subdir->next_file);
			}
			current = current->next_file;
		}
}

char *ft_strmode(t_dir *file_list, unsigned int mode, char *buf) 
{  
  static char chars[] = "rwxrwxrwx";
  int i;

  i = 1;
  buf[0] = file_list->type == FT_DIR ? 'd' : '-';
  while (i < 10)
  {
    buf[i] = (mode & (1 << (8 - i + 1))) ? chars[i - 1] : '-';
    i++;
  }
  return (buf);
}

void print_long(t_ls *ls, t_dir *file_list)
{
	t_dir *current;
	char *buf;

	current = file_list;
	while (current)
	{
		buf = ft_strnew(10);
		ft_printf("%-5s %5d %5s %5s %5d %5d %5d %5s\n", ft_strmode(current, current->rules, buf), current->links,
			getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name, current->size,
			gmtime(&current->time)->tm_mon, gmtime(&current->time)->tm_mday,
			ft_strrchr(current->path_file, '/') + 1);
		current = current->next_file;
	}
	current = file_list;
	if (ls->is_recursive == 1)
		while (current)
		{
			if (current->type == FT_DIR)
			{
				ft_printf("\n%s:\n", current->subdir->path_file);
				print_long(ls, current->subdir->next_file);
			}
			current = current->next_file;
		}
}

t_dir	*ft_create_file(char *fname, t_dir *subdir, int type)
{
	t_dir	*list;

	list = malloc(sizeof(t_dir));
	if (list)
	{
		list->path_file = fname;
		list->next_file = NULL;
		list->subdir = subdir;
		list->type = type;
		list->rules = 0;
		list->links = 0;
		list->user = 0;
		list->group = 0;
		list->size = 0;
		list->time = 0;
	}
	return (list);
}

void	list_push_back(t_dir **begin_list, char *fname, unsigned char type)
{
	t_dir	*current;

	if (*begin_list)
	{
		current = *begin_list;
		while (current->next_file)
			current = current->next_file;
		if (type == DT_DIR)
			current->next_file = ft_create_file(fname, NULL, FT_DIR);
		else if (type == DT_REG)
			current->next_file = ft_create_file(fname, NULL, FT_FILE);
	}

}

static int add_in_list(const char *bpath, t_ls *ls, t_dir **file_list)
{
	DIR *dir;
	char *path;
	struct dirent *d_entry;

	path = ft_strnew(0);
	if (!(dir = opendir(bpath)))
        return (-1);
	while ((d_entry = readdir(dir)))
	{
        if (d_entry->d_type == DT_REG)
        {
        	if (ft_strncmp(d_entry->d_name, ".", 1) == 0 && !ls->is_with_dot)
        		continue ;
        	path = ft_strjoin((*file_list)->path_file, "/");
        	path = ft_strjoin(path, d_entry->d_name);
        	list_push_back(file_list, path, d_entry->d_type);
        }
        else if (d_entry->d_type == DT_DIR)
		{
			if (ft_strncmp(d_entry->d_name, ".", 1) == 0 && !ls->is_with_dot)
				continue;
            path = ft_strjoin((*file_list)->path_file, "/");
        	path = ft_strjoin(path, d_entry->d_name);
            list_push_back(file_list, path, d_entry->d_type);
        }
	}
    closedir(dir);
    ls->is_recursive == 1 ? find_subdirs(ls, &(*file_list)->next_file) : NULL;
    return (1); 
}

void find_subdirs(t_ls *ls, t_dir **begin_list)
{
	t_dir *current;

	current = *begin_list;
	while (current != NULL)
	{
		if (current->type == FT_DIR)
		{
			//ft_printf("%s\n", current->path_file);
			current->subdir = ft_create_file(current->path_file, NULL, FT_DIR);
			add_in_list(current->path_file, ls, &(current->subdir));
		}
		current = current->next_file;
	}
}

void take_info(t_dir *file_list)
{
	t_dir *cur;
	struct stat buff;
	
	cur = file_list;
	while (cur)
	{
		stat(cur->path_file, &buff);
		cur->rules = buff.st_mode;
		cur->links = buff.st_nlink;
		cur->user = buff.st_uid;
		cur->group = buff.st_gid;
		cur->size = buff.st_size;
		cur->time = buff.st_mtime;
		cur = cur->next_file;
	}
	cur = file_list;
	while (cur != NULL)
	{
		if (cur->type == FT_DIR)
			take_info(cur->subdir);
		cur = cur->next_file;
	}
}



int	prepare_output(t_ls *ls)
{
	int i;
	t_dir	*file_list;

	file_list = ft_create_file(ls->path, NULL, FT_ROOT);
	i = 0;
	add_in_list(ls->path, ls, &file_list);
	ls->is_sort_by_time ? list_sort_by_time(&(file_list->next_file)) : list_sort_by_name(&(file_list->next_file));
	ls->is_reversed ? list_reverse(&(file_list->next_file)) : NULL;
	if (ls->long_format == 1)
	{
		take_info(file_list->next_file);
		print_long(ls, file_list->next_file);
	}
	else
		print_dir(ls, file_list->next_file);
	file_list = NULL;
	return (1);
}
