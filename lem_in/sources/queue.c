/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:39:13 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 18:41:30 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*add_to_queue(t_queue *queue, t_room *room)
{
	t_queue *new_list;

	new_list = (t_queue *)malloc(sizeof(t_queue));
	new_list->room_queue = room;
	new_list->next = queue;
	queue = new_list;
	return (queue);
}

t_room		*pop_from_queue(t_queue **queue)
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
