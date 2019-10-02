/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:53:33 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 19:11:57 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_color_else(t_dir *current, char *buf)
{
	if (current->type == FT_DIR)
		ft_printf("%-10s %2d %3d %5d %4d %-3s %2s %5s "CYAN"%-s"RESET"\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_uid, getgrgid(current->group)->gr_gid,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1);
	else if (current->type == FT_FILE_EXE)
		ft_printf("%-10s %2d %3d %5d %4d %-3s %2s %5s "RED_DARK"%-s"
			RESET"\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_uid, getgrgid(current->group)->gr_gid,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1);
	else
		ft_printf("%-10s %2d %3d %5d %4d %-3s %2s %5s %-s\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_uid, getgrgid(current->group)->gr_gid,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1);
}

static void		print_color_gr_user(t_dir *current, char *buf)
{
	if (current->type == FT_DIR)
		ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s "CYAN"%-s"RESET"\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1);
	else if (current->type == FT_FILE_EXE)
		ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s "RED_DARK"%-s"
			RESET"\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1);
	else
		ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s %-s\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1);
}

static void		print_color_long(t_ls *ls, t_dir *current, char *buf)
{
	char		*file_link;

	if (current->type == FT_LNK)
	{
		file_link = ft_strnew(current->size);
		readlink(current->path_file, file_link, current->size);
		ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s "MAGENTA_DARK"%-s"
			RESET" -> %3s\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1, file_link);
		free(file_link);
	}
	else if (ls->is_numb_gr_user)
		print_color_gr_user(current, buf);
	else
		print_color_else(current, buf);
}

static void		print_long2(t_ls *ls, t_dir *current, char *buf)
{
	char		*file_link;

	if (current->type == FT_LNK)
	{
		file_link = ft_strnew(current->size);
		readlink(current->path_file, file_link, current->size);
		ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s %-s -> %3s\n",
		ft_strmode(current, current->rules, buf), current->links,
		getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name,
		current->size, current->month, current->day, current->time,
		ft_strrchr(current->path_file, '/') + 1, file_link);
		free(file_link);
	}
	else if (ls->is_numb_gr_user)
		ft_printf("%-10s %2d %3d %5d %4d %-3s %2s %5s %-s\n",
			ft_strmode(current, current->rules, buf), current->links,
			getpwuid(current->user)->pw_uid, getgrgid(current->group)->gr_gid,
			current->size, current->month, current->day, current->time,
			ft_strrchr(current->path_file, '/') + 1);
	else
		ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s %-s\n",
			ft_strmode(current, current->rules, buf), current->links,
			getpwuid(current->user)->pw_name, getgrgid(current->group)->gr_name,
			current->size, current->month, current->day, current->time,
			ft_strrchr(current->path_file, '/') + 1);
}

void			print_long(t_ls *ls, t_dir *file_list)
{
	t_dir		*current;
	char		*buf;

	ft_printf("total %lld\n", ft_total(file_list));
	current = file_list;
	while (current)
	{
		buf = ft_strnew(11);
		if (ls->colors == 1)
			print_color_long(ls, current, buf);
		else
			print_long2(ls, current, buf);
		current = current->next_file;
		free(buf);
	}
}
