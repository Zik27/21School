/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:05:03 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/05 20:28:17 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int		fillit(t_tetriminos_fig *fig, char **map, int sqr_size)
{
	int x;
	int y;
	int coords[2];

	if (fig == NULL)
		return (1);
	y = 0;
	while (y++ < sqr_size - get_height(fig->data) + 1)
	{
		x = get_left_width(fig->data);
		while (x++ < sqr_size - get_right_width(fig->data))
			if (place(fig->data, map, x - 1, y - 1))
			{
				if (fillit(fig->next, map, sqr_size))
					return (1);
				else
				{
					coords[0] = y - 1;
					coords[1] = x - 1;
					clear_map(map, fig->data, 3, coords);
					place(NULL, NULL, 0, 0);
				}
			}
	}
	return (0);
}

int		search_square(int count)
{
	int i;

	i = 1;
	while (i * i < count)
		i++;
	return (i);
}

int		start_fillit(t_tetriminos_fig *head, char **map, int side_map)
{
	while (fillit(head, map, side_map) != 1)
	{
		free_map(map, side_map);
		if (!(map = build_map(++side_map)))
		{
			free_lst(&head);
			ft_putstr("error\n");
			return (0);
		}
	}
	print_map(map, side_map);
	free_map(map, side_map);
	free_lst(&head);
	return (1);
}

int		main(int argc, char **argv)
{
	int						count_fig;
	int						side_map;
	char					**map;
	static t_tetriminos_fig *head = NULL;

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
	if (!(start_fillit(head, map, side_map)))
		return (0);
}
