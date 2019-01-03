/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:05:03 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/03 18:32:24 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int	count_blocks;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit Tetriminos_file\n");
		return (0);
	}
	if (!(count_blocks = check_valid(argv[1])))
	{
		ft_putstr("error\n");
		return (0);
	}
	//printf("%d\n", count_blocks);
	//fillit(argv[1], count_blocks);
	return (0);
}