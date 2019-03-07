/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:44:15 by djast             #+#    #+#             */
/*   Updated: 2019/03/07 13:13:04 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS 
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <grp.h>
# include <time.h>
# include <pwd.h>
# include <dirent.h>
# define FT_FILE 1
# define FT_DIR 2
# define FT_ROOT 3
# define FT_FILE_EXE 4


/*
**	is_recursive - флаг -R - рекурсивный проход по папкам
**	is_with_dot - флаг -a - Показывать папки , в начале который стоит .
**	is_reversed - флаг -r - отсортировать в обратном порядке
**	is_sort_by_time - флаг -t - отсортировать по времени изменения
**	long_format - флаг -l - вывести в полном формате.
**	path - путь, откуда считывается ls.
**	dir_struct - структура типа DIR, которая описывает открытую папку.
*/

typedef struct		s_ls
{
	int is_recursive: 2;
	int is_with_dot: 2;
	int is_reversed: 2;
	int is_sort_by_time: 2;
	int long_format: 2;
	char *path;
} 					t_ls;

typedef struct		s_dir
{
	char			*path_file;
	struct	s_dir	*subdir;
	struct	s_dir	*next_file;
	int				type;
	int				rules;
	int				links;
	unsigned int	user;
	unsigned int	group;
	long long int	size;
	char			*month;
	char			*day;
	char			*time;
	long int		mtime;
	long int		mtime_nano;
	int				block;

} 					t_dir;

int					parsing_flags(int argc, char const *flags[], t_ls *ls);
void				print_struct(t_ls *ls);
int					prepare_output(t_ls *ls);
void                list_sort_by_name(t_dir **begin_list);
void    			list_reverse(t_dir **begin_list);
void                list_sort_by_time(t_dir **begin_list);

#endif