/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:46:09 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/05 19:08:45 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_link(t_room *room, t_room *link)
{
	t_link	*new_link;
	t_link	*tmp;
	t_link	*room_links;

	room_links = room->links;
	if (!(new_link = (t_link *)malloc(sizeof(t_link))))
		error("Malloc error");
	new_link->room_l = link;
	new_link->next = NULL;
	if (!room_links)
		room->links = new_link;
	else
	{
		while (room_links)
		{
			if (ft_strcmp(room_links->room_l->name, link->name) == 0)
				error("Duplicate links");
			tmp = room_links;
			room_links = room_links->next;
		}
		tmp->next = new_link;
	}
	room->count_links++;
}

t_room	*find_room(char *name, t_room **array, int left, int right)
{
	int		cmp;
	int		middle;


	//printf("name == %s, left == %d, right == %d\n", name, left, right);
	if (right - left <= 1)
		return (NULL);
	middle = (right + left) / 2;
	//printf("middle == %d, array_middle == %s\n", middle, array[middle]->name);
	if ((cmp = ft_strcmp(name, array[middle]->name)) == 0)
		return (array[middle]);
	else if (cmp > 0)
		return find_room(name, array, middle, right);
	else
		return find_room(name, array, left, middle);
	
}

int		search_links(char *name1, char *name2, t_map *map)
{
	t_room	*result1;
	t_room	*result2;
	t_room	**array;

	array = map->array_rooms;
	result1 = find_room(name1, array, -1, map->count_rooms);
	result2 = find_room(name2, array, -1, map->count_rooms);
	if (result1 == NULL || result2 == NULL)
		error("Room not found");
	else
	{
		create_link(result1, result2);
		create_link(result2, result1);
	}
	return (1);
}

void	parse_links(char **str, t_map *map)
{
	char	**ref;

	ref = ft_strsplit(*str, '-');
	if (!map->has_links)
		map->has_links = 1;
	if (map->prev_command)
	{
		free(ref);
		error("Invalid start/end");
	}
	if (ref[2] || !search_links(ref[0], ref[1], map))
	{
		free(ref);
		free(map);
		error("Invalid links");
	}
	free(ref);
}
