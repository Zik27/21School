/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:05:03 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/29 16:31:27 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("usage: ./fillit Tetriminos_file\n");
		return (0);
	}
	if (!check_valid(argv[1]))
	{
		ft_putstr("error\n");
		return (0);
	}
	//fillit(argv[1]);
}