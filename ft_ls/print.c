/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:53:33 by djast             #+#    #+#             */
/*   Updated: 2019/03/14 19:00:51 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_dir(t_ls *ls, t_dir *file_list)
{
	t_dir *current;

	current = file_list;
	while (current)
	{
		if (ls->colors == 1)
		{
			if (current->type == FT_FILE_EXE)
				ft_printf(RED_DARK"%s\n"RESET, ft_strrchr(
					current->path_file, '/') + 1);
			else if (current->type == FT_DIR)
				ft_printf(CYAN"%s\n"RESET, ft_strrchr(
					current->path_file, '/') + 1);
			else if (current->type == FT_LNK)
				ft_printf(MAGENTA_DARK"%s\n"RESET, ft_strrchr(
					current->path_file, '/') + 1);
			else
				ft_printf("%s\n", ft_strrchr(current->path_file, '/') + 1);
		}
		else
			ft_printf("%s\n", ft_strrchr(current->path_file, '/') + 1);
		current = current->next_file;
	}
}

char			*ft_strmode(t_dir *file_list, unsigned int mode, char *buf)
{
	static char	chars[] = "rwxrwxrwx";
	int			i;

	i = 1;
	if (file_list->type == FT_DIR)
		buf[0] = 'd';
	else if (file_list->type == FT_LNK)
		buf[0] = 'l';
	else
		buf[0] = '-';
	while (i < 10)
	{
		buf[i] = (mode & (1 << (8 - i + 1))) ? chars[i - 1] : '-';
		i++;
	}
	if (file_list->extended_attributes > 0)
		buf[10] = '@';
	else
		buf[10] = 0;
	return (buf);
}

long long		ft_total(t_dir *file_list)
{
	t_dir		*current;
	long long	total;

	total = 0;
	current = file_list;
	while (current)
	{
		total += current->block;
		current = current->next_file;
	}
	return (total);
}

static void		print_long2(t_ls *ls, t_dir *current, char *buf)
{
	if (ls->is_numb_gr_user)
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
	char		*file_link;

	//take_info(file_list);
	ft_printf("total %lld\n", ft_total(file_list));
	current = file_list;
	while (current)
	{
		buf = ft_strnew(11);
		
		if (current->type == FT_LNK)
		{
			file_link = ft_strnew(current->size);
			readlink(current->path_file, file_link, current->size);

			ft_printf("%-10s %2d %3s %5s %4d %-3s %2s %5s %-s -> %3s\n",
				ft_strmode(current, current->rules, buf), current->links,
				getpwuid(current->user)->pw_name,
				getgrgid(current->group)->gr_name,
				current->size, current->month, current->day, current->time,
				ft_strrchr(current->path_file, '/') + 1, file_link);
			//free(file_list);
		}
		else
			print_long2(ls, current, buf);
		current = current->next_file;
		free(buf);
		
	}
}
