/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:05:03 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/04 18:45:49 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int		search_square(int count)
{
	int i;

	i = 1;
	while (i * i < count)
		i++;
	return (i);
}

int		main(int argc, char **argv)
{
	int		count_fig;
	int		side_map;
	char	**map;
	static tetriminos_fig *head = NULL; // Head_list

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit Tetriminos_file\n");
		return (0);
	}
	if (!(count_fig = check_valid(argv[1], &head)))
	{
		free_lst(&head);
		ft_putstr("error\n");
		return (0);
	}
	side_map = search_square(count_fig * 4);
	if (!(map = build_map(side_map)))
	{
		free_lst(&head);
		ft_putstr("error\n");
		return (0);
	}

// map - КАРТА, side_map - размер стороны карты, head - начало списка



	// int i;
	// int j;
	// i = 0;
	// j = 0;
	// while (map[i])
	// {
	// 	printf("%s\n", map[i]);
	// 	i++;
	// }


	// tetriminos_fig	*current;
	// current = head;
	// while (current)
	// {
	// 	printf("%d\n", current->data[0]);
	// 	printf("%d\n", current->data[1]);
	// 	printf("%d\n", current->data[2]);
	// 	printf("\n");

	// 	current = current->next;
	// }
	// printf("count = %d\n", count_fig);
	// printf("ITOG = %d\n", side_map);
	free_map(map, side_map);
	return (0);
}