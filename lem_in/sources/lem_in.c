/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/30 18:42:48 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	free_map(t_map *map)
{
	free(map);
}

void	free_rooms(t_room *rooms)
{
	t_link	*link;
	t_room	*tmp;
	t_link	*tmp_l;

	while (rooms)
	{
		tmp = rooms;
		rooms = rooms->next;
		link = tmp->links;
		while (link)
		{
			tmp_l = link;
			link = link->next;
			free(tmp_l);
		}
		free(tmp);
	}
}

t_map	*init(void)
{
	t_map	*map;

	if ((map = (t_map *)malloc(sizeof(t_map))))
	{
		map->count_ants = 0;
		map->start = NULL;
		map->exit = NULL;
		map->prev_command = 0;
		map->has_links = 0;
		map->count_rooms = 0;
		map->array_rooms = NULL;
	}
	return (map);
}

t_room	*init_room(char *name, int x, int y)
{
	t_room	*room;

	if ((room = (t_room *)malloc(sizeof(t_room))))
	{
		room->x = x;
		room->y = y;
		room->count_links = 0;
		room->links = NULL;
		room->name = name;
	}
	return (room);
}



void	parse(t_map *map)
{
	char	*line;
	t_room	*rooms;
	int		count_rooms;

	count_rooms = 0;
	rooms = init_room(NULL, 0, 0);
	while (get_next_line(0, &line) == 1)
	{
		if (map->count_ants == 0)
			count_ants(line, map);
		else if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, ' '))
		{
			parse_rooms(line, map, &rooms);
			count_rooms++;
		}
		else if (line && ft_strchr(line, '-'))
			break ;
		else
			error("Invalid input");
		free(line);
	}
	list_to_array(map, rooms, count_rooms);
	sort_array_by_name(&map, count_rooms);
	map->count_rooms = count_rooms;
	parse_links(&line, map);
	while (get_next_line(0, &line) == 1)
	{
		if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, '-'))
			parse_links(&line, map);
		else
			error("Invalid input");
		free(line);
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
	// printf("START = %s, END = %s\n", map->start->name, map->exit->name);
	

	// if (!map->start || !map->exit || map->has_links != 1)
	// 	error("Invalid input");
	free_map(map);
	free_rooms(rooms);
}

int	main(void)
{
	t_map	*map;

	map = init();
	parse(map);
	return (0);
}