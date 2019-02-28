/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:44:15 by djast             #+#    #+#             */
/*   Updated: 2019/02/28 17:32:42 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS 
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <dirent.h>


/*
**	is_recursive - флаг -R - рекурсивный проход по папкам
**	is_with_dot - флаг -a - Показывать папки , в начале который стоит .
**	is_reversed - флаг -r - отсортировать в обратном порядке
**	is_sort_by_time - флаг -t - отсортировать по времени изменения
**	long_format - флаг -l - вывести в полном формате.
**	path - путь, откуда считывается ls.
**	dir_struct - структура типа DIR, которая описывает открытую папку.
**	is_dir - есть ли в аргументах директория
*/

typedef struct		s_ls
{
	int is_recursive: 2;
	int is_with_dot: 2;
	int is_reversed: 2;
	int is_sort_by_time: 2;
	int long_format: 2;
	int is_dir: 2;
	char *path;
	DIR *dir_struct;
} 					t_ls;

typedef struct		s_dir
{
	char			*fname;
	struct	s_dir	*subdir;
	struct	s_dir	*next_file;
} 					t_dir;

int					parsing_flags(int argc, char const *flags[], t_ls *ls);
void				print_struct(t_ls *ls);
int					prepare_output(int argc, char const **args, t_ls *ls);

#endif