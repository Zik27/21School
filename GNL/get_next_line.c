/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:24:26 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/18 14:24:28 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int get_next_line(const int fd, char **line)
{
	static char	*buf[BUFF_SIZE + 1];
	if (fd < 0 || line == NULL)
		return (-1);
	return (1);
}

int main()
{
	char **line;
	printf("%d", get_next_line(1, line));
}
