/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:26:52 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/29 18:46:06 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int	check_symbols(char *square)
{
	int	length;

	length = ft_strlen(square);
	while (*square)
	{
		if (!(*square == '\n' || *square == '#' || *square == '.'))
			return (0);
		square++;
	}
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
	if (!(width == 4 || width == 5))
		return (0);
	return (1);
}

int	check_valid(char *file)
{
	int	fd;
	int	ret;
	char buf[BUFF_SIZE + 1];

	if ((fd = open(file, O_RDONLY)) == -1 && (ret = read(fd, buf, 0) == -1))
		return (0);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (!check_symbols(buf) || !check_size(buf))
			return (0);
		//printf("%s", buf);
	}

	return (1);
}
