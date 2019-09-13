/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:17:42 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 15:27:44 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		delete_link(t_room **cur_room, t_room *next_room)
{
	t_link	*tmp;
	t_link	*after_list;
	t_link	*before_list;

	tmp = (*cur_room)->links;
	after_list = 0;
	before_list = (*cur_room)->links;
	while (tmp)
	{
		after_list = tmp->next;
		if (tmp->room_l == next_room)
		{
			if (tmp == (*cur_room)->links)
				(*cur_room)->links = after_list;
			else
				before_list->next = after_list;
			free(tmp);
			break ;
		}
		else
		{
			before_list = tmp;
			tmp = tmp->next;
		}
	}
}
