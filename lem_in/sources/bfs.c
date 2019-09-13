/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:24:08 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 15:26:38 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_queue		*add_to_queue(t_queue *queue, t_room *room)
{
	t_queue *new_list;

	new_list = (t_queue *)malloc(sizeof(t_queue));
	new_list->room_queue = room;
	new_list->next = queue;
	queue = new_list;
	return (queue);
}

static t_room		*pop_from_queue(t_queue **queue)
{
	t_queue *cur_list;
	t_room	*room;

	if ((*queue) == NULL)
		return (NULL);
	else if ((*queue)->next == NULL)
	{
		room = (*queue)->room_queue;
		free((*queue));
		(*queue) = NULL;
		return (room);
	}
	cur_list = (*queue);
	while (cur_list->next->next != NULL)
		cur_list = cur_list->next;
	room = cur_list->next->room_queue;
	free(cur_list->next);
	cur_list->next = NULL;
	return (room);
}

void				clear_full(t_room *room)
{
	t_room *cur_room;

	cur_room = room;
	while (cur_room != NULL)
	{
		cur_room->used = 0;
		cur_room->in_path = 0;
		cur_room->path_len = -1;
		cur_room = cur_room->next;
	}
}

void				clear_bfs(t_room *room)
{
	t_room *cur_room;

	cur_room = room;
	while (cur_room != NULL)
	{
		cur_room->used = 0;
		cur_room->path_len = -1;
		cur_room = cur_room->next;
	}
}

void				bfs(t_map *map)
{
	t_queue	*queue;
	t_room	*cur_room;
	t_link	*cur_link;
	int		step;

	queue = add_to_queue(NULL, map->start);
	map->start->path_len = 0;
	map->start->used = 1;
	while ((cur_room = pop_from_queue(&queue)) != NULL)
	{
		if (cur_room == map->exit)
			continue;
		step = cur_room->path_len;
		cur_link = cur_room->links;
		while (cur_link != NULL)
		{
			if (cur_link->room_l->in_path == 1)
			{
				cur_link = cur_link->next;
				continue;
			}
			else if (cur_link->room_l->used == 0)
			{
				cur_link->room_l->used = 1;
				cur_link->room_l->path_len = step + 1;
				queue = add_to_queue(queue, cur_link->room_l);
			}
			cur_link = cur_link->next;
		}
	}
}
