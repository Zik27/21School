/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:41:23 by djast             #+#    #+#             */
/*   Updated: 2019/03/01 17:06:05 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*init_struct()
{
	t_ls *ls;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->is_reversed = 0;
	ls->is_recursive = 0;
	ls->is_with_dot = 0;
	ls->is_sort_by_time = 0;
	ls->long_format = 0;
	ls->path = ".";
	return (ls);
}

// t_dir	*init_file_list()
// {
// 	t_dir *file_list;

// 	if (!(file_list = (t_dir *)malloc(sizeof(file_list))))
// 		return (NULL);
// 	file_list->fname = NULL;
// 	file_list->subdir = NULL;
// 	file_list->next_file = NULL;
	
// 	return (file_list);
// }

int main(int argc, char const *argv[])
{
	t_ls	*ls;
	int		error_code;

	ls = init_struct();
	if (argc > 1)
	{
		error_code = parsing_flags(argc, argv, ls);
		if (error_code == -1)
			ft_printf("ft_ls: illegal option -- ??\nusage: ls [-Ralrt] [file ...]\n");
		else if (error_code == -2)
			ft_printf("ft_ls: %s: No such file or directory\n", ls->path);
		if (error_code == -1 || error_code == -2)
			return (-1);
	}
	if (!(prepare_output(ls)))
		return (0);
	print_struct(ls);
	return (-1);
}
