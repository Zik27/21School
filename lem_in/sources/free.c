/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:56:12 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/04 11:57:28 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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