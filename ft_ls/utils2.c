/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:54:51 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 19:19:59 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*ft_strmode(t_dir *file_list, unsigned int mode, char *buf)
{
	static char	chars[] = "rwxrwxrwx";
	int			i;

	i = 1;
	if (file_list->type == FT_DIR)
		buf[0] = 'd';
	else if (file_list->type == FT_LNK)
		buf[0] = 'l';
	else if (file_list->type == FT_SOCK)
		buf[0] = 's';
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

char			*generate_name(t_dir **file_list, struct dirent *d)
{
	char *path;
	char *tmp;

	path = ft_strjoin((*file_list)->path_file, "/");
	tmp = path;
	path = ft_strjoin(path, d->d_name);
	free(tmp);
	return (path);
}
