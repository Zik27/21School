/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:53:20 by vurrigon          #+#    #+#             */
/*   Updated: 2019/03/07 13:35:35 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void find_subdirs(t_ls *ls, t_dir **begin_list);

void	print_dir(t_ls *ls, t_dir *file_list)
{
	t_dir *current;

	(void)ls;
	current = file_list;
	while (current)
	{
		if (current->type == FT_FILE_EXE)
			ft_printf(RED_DARK"%s\n"RESET, ft_strrchr(current->path_file, '/') + 1);
		else if (current->type == FT_DIR)
			ft_printf(CYAN"%s\n"RESET, ft_strrchr(current->path_file, '/') + 1);
		else
			ft_printf("%s\n", ft_strrchr(current->path_file, '/') + 1);
		current = current->next_file;
	}
	// current = file_list;
	// if (ls->is_recursive == 1)
	// 	while (current)
	// 	{
	// 		if (current->type == FT_DIR)
	// 		{
	// 			ft_printf("\n%s:\n", current->subdir->path_file);
	// 			print_dir(ls, current->subdir->next_file);
	// 		}
	// 		current = current->next_file;
	// 	}
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

long long ft_total(t_dir *file_list)
{
	t_dir *current;
	long long total;

	total = 0;
	current = file_list;
	while (current)
	{
		total += current->block;
		current = current->next_file;
	}
	return (total);
}

void print_long(t_ls *ls, t_dir *file_list)
{
	t_dir *current;
	char *buf;
	long long total;

	total = ft_total(file_list);
	printf("total %lld\n", total);

	current = file_list;

	while (current)
	{
		buf = ft_strnew(10);
		ft_printf("%-5s %4d %4s %5s %6d %-4s %s %5s %-5s\n", ft_strmode(current, current->rules, buf), current->links,
			getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name, current->size,
			current->month, current->day, current->time,
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
	t_dir		*list;
	struct stat	status;
	char **mtime;
	int i;

	stat(fname, &status);
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
		mtime = ft_strsplit(ctime(&status.st_mtime), ' ');
		list->month = ft_strdup(mtime[1]);
		list->day = ft_strdup(mtime[2]);
		list->time = ft_strsub(mtime[3], 0, 5);
		list->mtime = status.st_mtimespec.tv_sec;
		list->mtime_nano = status.st_mtimespec.tv_nsec;
		list->block = status.st_blocks;
		i = 0;
		while (mtime[i])
		{
			free(mtime[i]);
			i++;
		}
		free(mtime);
	}
	return (list);
}

void	list_push_back(t_dir **begin_list, char *fname, unsigned char type)
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
	}
}

void delete_branch(t_dir **file_list)
{
	t_dir *current;
	t_dir *next;

	current = *file_list;
	next = NULL;
	if (current)
		next = (*file_list)->next_file;

	while (next)
	{
	//	printf("DELETED: %s with month: %s, day: %s, time: %s\n", current->path_file, current->month, current->day, current->time);
		free(current->month);
		free(current->day);
		free(current->time);
		free(current->path_file);
		free(current);
		current = next;
		next = current->next_file;
	}
	//printf("LAST DELETED: %s with month: %s, day: %s, time: %s\n", current->path_file, current->month, current->day, current->time);
	free(current->path_file);
	free(current->month);
	free(current->day);
	free(current->time);
	free(current);
	current = NULL;
}

static int add_in_list(const char *bpath, t_ls *ls, t_dir **file_list)
{
	DIR *dir;
	char *path;
	struct dirent *d_entry;
	int dirs;
	char *tmp;

	dirs = 0;
	if (!(dir = opendir(bpath)))
        return (-1);
    if (ft_strcmp((*file_list)->path_file, ".") != 0)
    	 ls->long_format == 0 ? (void)ft_printf("\n%s:\n", (*file_list)->path_file) : NULL;
	while ((d_entry = readdir(dir)))
	{
        if (d_entry->d_type == DT_REG)
        {
        	if (ft_strncmp(d_entry->d_name, ".", 1) == 0 && !ls->is_with_dot)
        		continue ;
        	path = ft_strjoin((*file_list)->path_file, "/");
        	tmp = path;
        	path = ft_strjoin(path, d_entry->d_name);
        	free(tmp);
        	list_push_back(file_list, path, d_entry->d_type);
        }
        else if (d_entry->d_type == DT_DIR)
		{
			if (ft_strncmp(d_entry->d_name, ".", 1) == 0 && !ls->is_with_dot)
				continue;
            path = ft_strjoin((*file_list)->path_file, "/");
            tmp = path;
        	path = ft_strjoin(path, d_entry->d_name);
        	free(tmp);
            list_push_back(file_list, path, d_entry->d_type);
            dirs = 1;
        }
        else
        	continue;
        //ls->long_format == 0 ? (void)printf("CREATED: %s\n", path) : NULL;
	}
    closedir(dir);
    list_sort_by_name(&((*file_list)->next_file));
	ls->is_sort_by_time ? list_sort_by_time(&((*file_list)->next_file)) : list_sort_by_name(&((*file_list)->next_file));
	ls->is_reversed ? list_reverse(&((*file_list)->next_file)) : NULL;
	ls->long_format == 0 ? print_dir(ls, (*file_list)->next_file) : NULL;

    ls->is_recursive == 1 ? find_subdirs(ls, &(*file_list)->next_file) : NULL;
    //ls->long_format == 0 ? delete_branch(file_list);
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
	char **parsed_time;
	int i;
	
	cur = file_list;
	while (cur)
	{
		stat(cur->path_file, &buff);
		cur->rules = buff.st_mode;
		cur->links = buff.st_nlink;
		cur->user = buff.st_uid;
		cur->group = buff.st_gid;
		cur->size = buff.st_size;
		parsed_time = ft_strsplit(ctime(&buff.st_mtime), ' ');
		cur->month = ft_strdup(parsed_time[1]);
		cur->day = ft_strdup(parsed_time[2]);
		cur->time = ft_strsub(parsed_time[3], 0, 5);
		cur->block = buff.st_blocks;
		cur = cur->next_file;
		i = 0;
		while (parsed_time[i])
		{
			free(parsed_time[i]);
			i++;
		}
		free(parsed_time);
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
	// free(file_list->month);
	// free(file_list->day);
	// free(file_list->time);
	// free(file_list);
	// list_sort_by_name(&(file_list->next_file));
	// ls->is_sort_by_time ? list_sort_by_time(&(file_list->next_file)) : list_sort_by_name(&(file_list->next_file));
	// ls->is_reversed ? list_reverse(&(file_list->next_file)) : NULL;
	if (ls->long_format == 1)
	{
		take_info(file_list->next_file);
		print_long(ls, file_list->next_file);
	}
	//else
	//	print_dir(ls, file_list->next_file);
	file_list = NULL;
	return (1);
}
