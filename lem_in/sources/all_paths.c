/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:33:10 by djast             #+#    #+#             */
/*   Updated: 2019/09/05 18:06:04 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path		*add_to_path(t_path *path, t_room *room)
{
	t_path *new_list;

	new_list = (t_path *)malloc(sizeof(t_path));
	new_list->room_path = room;
	new_list->next = path;
	path = new_list;
	return (path);
}

static t_paths		*add_to_paths(t_paths *paths, t_path *path)
{
	t_paths *new_list;

	new_list = (t_paths *)malloc(sizeof(t_paths));
	new_list->path = path;
	new_list->next = paths;
	paths = new_list;
	return (paths);
}


static t_path		*get_one_path(t_map *map, int steps)
{
	t_room	*cur_room;
	t_link	*cur_link;
	t_path	*path;

	path = NULL;
	cur_room = map->exit;
	path = add_to_path(path, map->exit);
	cur_link = cur_room->links;
	while (cur_link != NULL)
	{
		if (cur_link->room_l == map->start)
		{
			path = add_to_path(path, map->start);
			return (path);
		}
		if (cur_link->room_l->path_len == steps && cur_link->room_l->in_path == 0)
		{
			cur_link->room_l->in_path = 1;
			path = add_to_path(path, cur_link->room_l);
			steps -= 1;
			cur_room = cur_link->room_l;
			cur_link = cur_room->links;
		}
		else
			cur_link = cur_link->next;
	}
	return (NULL);
}

static int			check_links(t_room *cur_room)
{
	t_link	*cur_link;

	cur_link = cur_room->links;
	while (cur_link != NULL)
	{
		if (cur_link->room_l->in_path == 0)
			return (1);
		cur_link = cur_link->next;
	}
	return (0);
}

static void			print_paths(t_paths *paths)
{
	t_path *cur_path;
	t_paths *cur_paths;

	cur_paths = paths;
	while (cur_paths != NULL )
	{
		cur_path = cur_paths->path;
		while (cur_path != NULL)
		{
			printf("%s -> ", cur_path->room_path->name);
			cur_path = cur_path->next;
		}
		printf("\n");
		cur_paths = cur_paths->next;
	}

}

t_paths				*get_all_paths(t_map *map)
{
	int		steps;
	t_paths	*paths;
	t_path	*path;

	steps = 0;
	paths = NULL;
	while (check_links(map->start) == 1 &&
											check_links(map->exit) == 1)
	{
		path = get_one_path(map, steps);
		if (path != NULL)
		{
			paths = add_to_paths(paths, path);
			paths->size = steps;
		}
		else
			steps++;
		
	}
	print_paths(paths);
	return (paths);
}