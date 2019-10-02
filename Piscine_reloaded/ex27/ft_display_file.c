/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 12:57:06 by vurrigon          #+#    #+#             */
/*   Updated: 2018/11/23 10:59:07 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_display_file.h"

void	ft_display_file(char *file)
{
	int		fd;
	int		ret;
	char	buf[BUF_SIZE + 1];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_putstr("File name missing.\n");
	else
	{
		while ((ret = read(fd, buf, BUF_SIZE)))
			buf[ret] = '\0';
		if (close(fd) == -1)
			ft_putstr("Error close");
		else
			ft_putstr(buf);
	}
}

int		main(int argc, char **argv)
{
	if (argc > 2)
		ft_putstr("Too many arguments.\n");
	else if (argc == 1)
		ft_putstr("File name missing.\n");
	else
		ft_display_file(argv[1]);
	return (0);
}
