/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:26:52 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/04 15:42:06 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int	check_neigh(char *square)
{
	int i;
	int	count_conn;

	count_conn = 0;
	i = 0;
	while (i < 20)
	{
		if (square[i] == '#')
		{
			if ((i + 1) < 20 && square[i + 1] == '#')
				count_conn++;
			if ((i + 5) < 20 && square[i + 5] == '#')
				count_conn++;
			if ((i - 1) >= 0 && square[i - 1] == '#')
				count_conn++;
			if ((i - 5) >= 0 && square[i - 5] == '#')
				count_conn++;
		}
		i++;
	}
	if (count_conn == 6 || count_conn == 8)
		return (1);
	return (0);
}

int	check_symbols(char *square)
{
	int	count_grid;

	count_grid = 0;
	while (*square)
	{
		if (!(*square == '\n' || *square == '#' || *square == '.'))
			return (0);
		if (*square == '#')
			count_grid++;
		square++;
	}
	if (count_grid != 4)
		return (0);
	return (1);
}

int	check_size(char *square)
{
	int	width;
	int	length;
	int len_sq;

	len_sq = ft_strlen(square) - (ft_strlen(square) % 5);
	length = 0;
	width = 0;
	while (len_sq)
	{
		if (*square != '\n')
			length++;
		else
		{
			if (length != 4)
				return (0);
			length = 0;
			width++;
		}
		square++;
		len_sq--;
	}
	if (!(width == 4))
		return (0);
	return (1);
}

/*
** Return 0 if error or Number - count of blocks
*/

int	check_valid(char *file, tetriminos_fig **head)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	int		count;

	count = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (!check_symbols(buf) || !check_size(buf) || !check_neigh(buf))
			return (0);
		if(!prepare_data(buf, head))
			return (0);
		count++;
	}
	if (close(fd) == -1)
		return (0);
	if (count > 26 || count < 1)
		return (0);
	return (count);
}
