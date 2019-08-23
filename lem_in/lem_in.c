/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/23 16:48:57 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

t_map	*init(void)
{
	t_map	*map;

	if ((map = (t_map *)ft_memalloc(sizeof(t_map))))
	{
		map->count_ants = 0;
		map->has_start = 0;
		map->has_exit = 0;
		map->prev_step = 0;
	}
	return (map);
}

t_room	*init_room(char *name, int x, int y)
{
	t_room	*room;

	if ((room = (t_room *)ft_memalloc(sizeof(t_room))))
	{
		room->x = x;
		room->y = y;
		room->count_links = 0;
		room->links = NULL;
		room->name = name;
		room->next = NULL;
	}
	return (room);
}

void	read_map(t_map *map)
{
	char	*line;
	t_room	*rooms;

	rooms = init_room(NULL, 0, 0);
	while (get_next_line(0, &line) == 1)
	{
		if (map->count_ants == 0)
			count_ants(line, map);
		else if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, ' '))
			parse_rooms(line, map, rooms);
		else if (line && ft_strchr(line, '-'))
			parse_links(line, map, rooms);
		else
			error("Invalid input");
	}
	// printf("RESULT:\n");
	// while (rooms)
	// {
	// 	printf("%s x=%d y=%d links=%d\n", rooms->name, rooms->x, rooms->y, rooms->count_links);
		
	// 	t_link	*link;
	// 	link = rooms->links;

	// 	while (link)
	// 	{
	// 		printf("LINK === %s\n", link->name);
	// 		link = link->next;
	// 	}
	// 	rooms = rooms->next;
	// }
	if (map->has_start != 1 || map->has_exit != 1)
		error("Invalid input");
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = init();
	read_map(map);
	return (0);
}