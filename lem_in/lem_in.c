/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/20 15:39:30 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

t_map	*init(void)
{
	t_map	*map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->count_ants = 0;
	map->rooms = NULL;
	return (map);
}

void	read_map(t_map *map)
{
	char	*line;

	while (get_next_line(0, &line) == 1)
	{
		if (map->count_ants == 0)
			count_ants(line, map);
		
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = init();
	read_map(map);
	return (0);
}