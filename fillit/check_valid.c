/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:26:52 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/29 17:42:24 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

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
		printf("%s", buf);
	}

	return (1);
}
