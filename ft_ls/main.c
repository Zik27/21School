/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:41:23 by djast             #+#    #+#             */
/*   Updated: 2019/03/14 16:54:22 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls		*init_struct(void)
{
	t_ls *ls;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->is_reversed = 0;
	ls->is_recursive = 0;
	ls->is_with_dot = 0;
	ls->is_sort_by_time = 0;
	ls->long_format = 0;
	ls->not_sort = 0;
	ls->is_sort_by_size = 0;
	ls->is_almost_all = 0;
	ls->is_numb_gr_user = 0;
	ls->colors = 0;
	ls->path = NULL;
	ls->multiple_files = 0;
	ls->first_time = 1;
	return (ls);
}

int			main(int argc, char const *argv[])
{
	t_ls	*ls;
	int		error_code;

	ls = init_struct();
	if (argc > 1)
	{
		error_code = parsing_flags(argc, argv, ls);
		if (error_code < -3)
		{
			ft_printf("ft_ls: illegal option -- %c\n", -error_code);
			ft_printf("usage: ls [-AGSRaflnrt] [file ...]\n");
			return (1);
		}
	}
	else
	{
		ls->path = (char **)malloc(sizeof(char *) * 2);
		ls->path[0] = ".";
		ls->path[1] = NULL;
	}
	prepare_output(ls);
	free(ls->path);
	free(ls);
	return (0);
}
