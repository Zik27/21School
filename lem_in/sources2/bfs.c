/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:24:08 by djast             #+#    #+#             */
/*   Updated: 2019/09/10 10:42:09 by djast            ###   ########.fr       */
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

// static void			print_queue(t_queue *queue)
// {
// 	t_queue *cur_queue;

// 	if (queue == NULL)
// 		return ;
// 	cur_queue = queue;
// 	while (cur_queue != NULL)
// 	{
// 		printf("%s -> ", cur_queue->room_queue->name);
// 		cur_queue = cur_queue->next;
// 	}
// 	printf("\n");
// }

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
			if (cur_link->room_l->used == 0)
			{
				cur_link->room_l->used = 1;
				cur_link->room_l->path_len = step + 1;
				queue = add_to_queue(queue, cur_link->room_l);
			}
			cur_link = cur_link->next;
		}
	}
}