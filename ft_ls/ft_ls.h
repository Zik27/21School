/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:44:15 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 19:10:11 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <grp.h>
# include <time.h>
# include <pwd.h>
# include <dirent.h>
# define FT_FILE 1
# define FT_DIR 2
# define FT_ROOT 3
# define FT_FILE_EXE 4
# define FT_LNK 5
# define FT_SOCK 6

/*
**	bonus:
**  -S - сортировка по размеру
**  -f - не сортироват вывод
**  color - выполняемые файлы и директории выделяются определенным цветом
**  -A - не выводить "." и ".."
**  -n - с флагом -l выводит id пользователя и группы вместо имени
**  -G - выводить цвет
*/

/*
**	is_recursive - флаг -R - рекурсивный проход по папкам
**	is_with_dot - флаг -a - Показывать папки , в начале который стоит .
**	is_reversed - флаг -r - отсортировать в обратном порядке
**	is_sort_by_time - флаг -t - отсортировать по времени изменения
**	long_format - флаг -l - вывести в полном формате.
**  not_sort - флаг -f - не сортировать вывод
**	is_sort_by_size - флаг -S - сортировка по размеру
**	is_almost_all - флаг -A - не выводить "." и ".."
**	is_numb_gr_user - флаг -n - с флагом -l выводит id пользователя и группы
**	colors - флаг -G - выводить цвет
**	multiple_files - 1, если файлов больше одного
**  first_time - 1, если это первая папка
**
**
** path - путь, откуда считывается ls.
*/

typedef struct		s_ls
{
	int		is_recursive: 2;
	int		is_with_dot: 2;
	int		is_reversed: 2;
	int		is_sort_by_time: 2;
	int		long_format: 2;
	int		not_sort: 2;
	int		is_sort_by_size : 2;
	int		is_almost_all : 2;
	int		is_numb_gr_user : 2;
	int		colors : 2;
	int		multiple_files : 2;
	int		first_time : 2;
	char	**path;
}					t_ls;

typedef struct		s_dir
{
	char			*path_file;
	struct s_dir	*subdir;
	struct s_dir	*next_file;
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
	int				extended_attributes;
}					t_dir;

int					parsing_flags(int argc, char const *flags[], t_ls *ls);
void				print_struct(t_ls *ls);
int					prepare_output(t_ls *ls);
void				list_sort_by_name(t_dir **begin_list);
void				list_reverse(t_dir **begin_list);
void				list_sort_by_time(t_dir **begin_list);
void				list_sort_by_size(t_dir **begin_list);
int					ft_size_array(char **str);
void				take_info(t_dir *file_list);
void				print_dir(t_ls *ls, t_dir *file_list);
void				print_long(t_ls *ls, t_dir *file_list);
void				delete_branch(t_dir **file_list);
void				list_reverse(t_dir **begin_list);
void				find_subdirs(t_ls *ls, t_dir **begin_list,
									char *start_path);
long long			ft_total(t_dir *file_list);
void				list_push_back(t_dir **begin_list, char *fname,
									unsigned char type);
t_dir				*ft_create_file(char *fname, t_dir *subdir, int type);
char				*ft_strmode(t_dir *file_list, unsigned int mode, char *buf);
char				*generate_name(t_dir **file_list, struct dirent *d);
#endif
