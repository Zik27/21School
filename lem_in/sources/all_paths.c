/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:33:10 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 19:01:25 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path		*add_to_path(t_path *path, t_room *room)
{
	t_path	*new_list;

	new_list = (t_path *)malloc(sizeof(t_path));
	new_list->room_path = room;
	new_list->next = path;
	path = new_list;
	return (path);
}

static t_paths		*add_to_paths(t_paths *paths, t_path *path)
{
	t_paths	*new_list;

	new_list = (t_paths *)malloc(sizeof(t_paths));
	new_list->path = path;
	new_list->next = paths;
	paths = new_list;
	return (paths);
}

static t_path		*get_one_path(t_map *map, int status, t_path *path)
{
	t_room	*cur_room;
	t_link	*cur_link;

	cur_room = map->exit;
	map->min_steps = cur_room->path_len - 1;
	while (map->min_steps != -1)
	{
		cur_link = cur_room->links;
		while (cur_link != NULL)
		{
			cur_link = cur_link->room_l == map->start && cur_room == map->exit
							&& status == 1 ? cur_link->next : cur_link;
			if (cur_link->room_l->path_len == map->min_steps)
			{
				cur_link->room_l->in_path = 1;
				path = add_to_path(path, cur_link->room_l);
				map->min_steps -= 1;
				cur_room = cur_link->room_l;
				break ;
			}
			else
				cur_link = cur_link->next;
		}
	}
	return (path);
}

static t_paths		*get_all_paths(t_map *map, t_room *rooms)
{
	t_paths	*paths;
	t_path	*path;

	paths = NULL;
	while (map->exit->path_len != -1)
	{
		path = get_one_path(map, map->has_start_stop,
											add_to_path(NULL, map->exit));
		if (path->room_path == map->start && path->next->room_path == map->exit)
		{
			delete_link(&(map->start), map->exit);
			delete_link(&(map->exit), map->start);
			map->has_start_stop = 1;
		}
		paths = add_to_paths(paths, path);
		paths->size = map->exit->path_len;
		clear_bfs(rooms);
		bfs(map);
	}
	return (paths);
}

t_paths				*get_all_paths_prepare(t_map *map, t_room *rooms,
											int status)
{
	t_paths	*paths;

	map->has_start_stop = 0;
	clear_full(rooms);
	bfs(map);
	if (map->exit->path_len == -1 && status == 1)
		error("No path found");
	paths = get_all_paths(map, rooms);
	if (map->has_start_stop == 1)
	{
		create_link(map->start, map->exit);
		create_link(map->exit, map->start);
	}
	return (paths);
}
