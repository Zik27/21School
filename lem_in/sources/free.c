/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:56:12 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 15:26:11 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_map(t_map *map)
{
	t_room	**rooms;
	int		i;

	i = 0;
	rooms = map->array_rooms;
	free(rooms);
	free(map);
}

void		free_rooms(t_room *rooms)
{
	t_link	*link;
	t_room	*tmp;
	t_link	*tmp_l;

	while (rooms)
	{
		tmp = rooms;
		rooms = rooms->next;
		link = tmp->links;
		free(tmp->name);
		while (link)
		{
			tmp_l = link;
			link = link->next;
			free(tmp_l);
		}
		free(tmp);
	}
}

static void	free_path(t_path *path)
{
	t_path	*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

void		free_paths(t_paths *current)
{
	t_paths *before;

	while (current)
	{
		before = current;
		current = current->next;
		free_path(before->path);
		free(before);
	}
}

void		free_input(t_file_txt *input)
{
	t_file_txt *before;

	while (input)
	{
		before = input;
		input = input->next;
		free(before->text);
		free(before);
	}
}
