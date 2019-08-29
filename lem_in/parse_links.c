/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:46:09 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/29 16:14:25 by vurrigon         ###   ########.fr       */
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

int		check_count_dash(char **link)
{
	int	i;

	i = 0;
	while (link[i])
		i++;
	if (i > 2)
		return (0);
	return (1);
}

int		search_other_link(char *name_link, char	*other_name, t_room *rooms)
{
	while (rooms)
	{
		if (ft_strcmp(other_name, rooms->name) == 0)
		{
			rooms->count_links++;
			create_link(name_link, rooms);
			return (1);
		}
		rooms = rooms->next;
	}
	return (0);
}

int		search_links(char *name1, char *name2, t_room *rooms)
{
	//printf("name1 === %s, name2 === %s\n", name1, name2);
	while (rooms)
	{
		if (ft_strcmp(name1, rooms->name) == 0)
		{
			rooms->count_links++;
			create_link(name2, rooms);
			if (!search_other_link(name1, name2, rooms->next))
				return (0);
			return (1);
		}
		else if (ft_strcmp(name2, rooms->name) == 0)
		{
			rooms->count_links++;
			create_link(name1, rooms);
			if (!search_other_link(name2, name1, rooms->next))
				return (0);
			return (1);
		}
		rooms = rooms->next;
	}
	return (0);
}

void	parse_links(char *str, t_map *map, t_room *rooms)
{
	char	**ref;

	ref = ft_strsplit(str, '-');
	if (!map->has_links)
		map->has_links = 1;
	if (map->prev_command)
	{
		free(ref);
		error("Invalid start/end");
	}
	if (!rooms->name && !rooms->x && !rooms->y)
	{
		free(ref);
		error("The room is not defined");
	}
	if (!check_count_dash(ref) || !search_links(ref[0], ref[1], rooms))
	{
		free(ref);
		free(map);
		error("Invalid links");
	}
	free(ref);
}
