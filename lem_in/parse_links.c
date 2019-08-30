/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:46:09 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/30 18:29:05 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_link(char *name_link, t_room *rooms)
{
	t_link	*new_link;
	t_link	*tmp;

	tmp = rooms->links;
	if ((new_link = (t_link *)ft_memalloc(sizeof(t_link))))
	{
		new_link->name = name_link;
		new_link->next = NULL;
	}
	if (!rooms->links)
		rooms->links = new_link;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_link;
	}
}

int		search_links(char *name1, char *name2, t_map *map)
{
	t_room	**array;
	t_room	*origin_room;

	array = map->array_rooms;
	printf("name1 === %s, name2 === %s\n", name1, name2);
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
