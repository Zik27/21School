/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:53:20 by vurrigon          #+#    #+#             */
/*   Updated: 2019/02/28 17:38:04 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir(t_dir *file_list)
{
	while (file_list)
	{
		ft_printf("%s\n", file_list->fname);
		file_list = file_list->next_file;
	}
}

void	list_sort_by_name(t_dir **begin_list)
{
	t_dir	*list;
	char	*tmp;
	int		flag;

	list = *begin_list;
	if (list == 0)
		return ;
	while (1)
	{
		list = *begin_list;
		flag = 0;
		while (list->next_file != 0)
		{
			if (ft_strcmp(list->fname, (list->next_file)->fname) > 0)
			{
				flag = 1;
				tmp = list->fname;
				list->fname = list->next_file->fname;
				list->next_file->fname = tmp;
			}
			list = list->next_file;
		}
		if (flag == 0)
			break ;
	}
}

void	list_sort_by_name_rev(t_dir **begin_list)
{
	t_dir	*list;
	char	*tmp;
	int		flag;

	list = *begin_list;
	if (list == 0)
		return ;
	while (1)
	{
		list = *begin_list;
		flag = 0;
		while (list->next_file != 0)
		{
			if (ft_strcmp(list->fname, (list->next_file)->fname) < 0)
			{
				flag = 1;
				tmp = list->fname;
				list->fname = list->next_file->fname;
				list->next_file->fname = tmp;
			}
			list = list->next_file;
		}
		if (flag == 0)
			break ;
	}
}

t_dir	*ft_create_file(char *fname)
{
	t_dir	*list;

	list = malloc(sizeof(t_dir));
	if (list)
	{
		list->fname = fname;
		list->next_file = NULL;
		list->subdir = NULL;
	}
	return (list);
}

void	list_push_back(t_dir **begin_list, char *fname)
{
	t_dir	*current;

	if (*begin_list)
	{
		current = *begin_list;
		while (current->next_file)
			current = current->next_file;
		current->next_file = ft_create_file(fname);
	}
	else
		*begin_list = ft_create_file(fname);
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
        	list_push_back(file_list, d_entry->d_name);
        }
        else if (d_entry->d_type == DT_DIR)
		{
			if (ft_strncmp(d_entry->d_name, ".", 1) == 0 && !ls->is_with_dot)
				continue;
            path = ft_strjoin(path, bpath);
            path = ft_strjoin(path, "/");
            path = ft_strjoin(path, d_entry->d_name);
            path = ft_strnew(0);
            list_push_back(file_list, d_entry->d_name);
        }
	}
    closedir(dir);
    return (1); 
}

int	prepare_output(int argc, char const **args, t_ls *ls)
{
	int i;
	t_dir	*file_list;

	file_list = NULL;
	i = 0;
	if (!ls->is_dir)
	{
		add_in_list(".", ls, &file_list);
		ls->is_reversed ? list_sort_by_name_rev(&file_list) : list_sort_by_name(&file_list);
		print_dir(file_list);
		file_list = NULL;
	}
	else
		while (i++ < argc - 1)
		{
			add_in_list(args[i], ls, &file_list);
			ls->is_reversed ? list_sort_by_name_rev(&file_list) : list_sort_by_name(&file_list);
			print_dir(file_list);
			file_list = NULL;
		}
	return (1);
}
