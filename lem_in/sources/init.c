/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:52:57 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 15:33:00 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_map		*init(void)
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
		map->input = NULL;
		map->count_out_line = -1;
	}
	return (map);
}

t_file_txt	*init_input_file(char *text)
{
	t_file_txt	*file;

	if ((file = (t_file_txt *)malloc(sizeof(t_file_txt))))
	{
		file->text = text;
		file->next = NULL;
	}
	return (file);
}

t_links		*init_links(t_room *room_start, t_room *room_end)
{
	t_links	*links;

	if ((links = (t_links *)malloc(sizeof(t_links))))
	{
		links->room_start = room_start;
		links->room_end = room_end;
		links->next = NULL;
	}
	return (links);
}

t_ants		*init_ants(t_path *cur_path)
{
	t_ants	*ants;

	if ((ants = (t_ants *)malloc(sizeof(t_ants))))
	{
		ants->cur_path = cur_path;
		if (cur_path == NULL)
		{
			ants->x = 0;
			ants->y = 0;
			ants->speed_x = 0;
			ants->speed_y = 0;
		}
		else
		{
			ants->x = cur_path->room_path->x;
			ants->y = cur_path->room_path->y;
			ants->speed_x = (cur_path->next->room_path->x -
				cur_path->room_path->x) / SPEED;
			ants->speed_y = (cur_path->next->room_path->y -
				cur_path->room_path->y) / SPEED;
		}
		ants->next = NULL;
	}
	return (ants);
}

t_room		*init_room(char *name, int x, int y)
{
	t_room	*room;

	if ((room = (t_room *)malloc(sizeof(t_room))))
	{
		room->x = x;
		room->y = y;
		room->path_len = -1;
		room->used = 0;
		room->in_path = 0;
		room->count_links = 0;
		room->links = NULL;
		room->name = name;
		room->ant_id = -1;
		room->next = NULL;
	}
	return (room);
}
