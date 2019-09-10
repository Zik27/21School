/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:52:57 by djast             #+#    #+#             */
/*   Updated: 2019/09/07 20:18:59 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

t_room	*init_room(char *name, int x, int y)
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