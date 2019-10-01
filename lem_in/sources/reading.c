/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:04:29 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 18:24:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		reading_links(char *line, t_map *map, t_room *rooms,
													int count_rooms)
{
	if (!rooms->x && !rooms->y && !rooms->name)
		error("Invalid input");
	list_to_array(map, rooms, count_rooms);
	sort_array_by_name(&map, count_rooms);
	map->count_rooms = count_rooms;
	add_to_file_txt(&map->input, line);
	parse_links(&line, map);
	while (get_next_line(0, &line) == 1)
	{
		if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, '-'))
			parse_links(&line, map);
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
}

void		reading_rooms(t_map *map, t_room **rooms)
{
	char		*line;

	map->count_rooms = 0;
	while (get_next_line(0, &line) == 1)
	{
		if (map->count_ant == 0)
			count_ants(line, map);
		else if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, ' '))
		{
			parse_rooms(line, map, rooms);
			map->count_rooms++;
		}
		else if (line && ft_strchr(line, '-'))
		{
			reading_links(line, map, *rooms, map->count_rooms);
			break ;
		}
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
	if (!map->start || !map->exit || map->has_links != 1)
		error("Invalid input");
}
