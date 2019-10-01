/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:17:42 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 18:46:51 by vurrigon         ###   ########.fr       */
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

t_paths		*try_to_find_new_paths(t_path *cur_path, t_map *map, t_room *rooms)
{
	t_paths		*paths;

	delete_link(&(cur_path->room_path), cur_path->next->room_path);
	delete_link(&(cur_path->next->room_path), cur_path->room_path);
	paths = get_all_paths_prepare(map, rooms, 0);
	reverse_paths(&paths);
	map->path = choose_path(map->count_ant, paths, map);
	create_link(cur_path->room_path, cur_path->next->room_path);
	create_link(cur_path->next->room_path, cur_path->room_path);
	return (paths);
}

void		take_paths_to_optimizate(t_paths *cur_paths, t_map *map,
									t_room *rooms)
{
	t_path		*cur_path;
	t_paths		*paths;

	cur_path = cur_paths->path;
	while (cur_path->next != NULL && map->is_best == 0)
	{
		paths = try_to_find_new_paths(cur_path, map, rooms);
		if (map->min_lines > map->count_line)
		{
			free_paths(map->best_paths);
			map->best_paths = paths;
			map->min_lines = map->count_line;
			map->best_path_count = map->path;
			map->is_best = 1;
			break ;
		}
		else
			free_paths(paths);
		cur_path = cur_path->next;
	}
	cur_paths = cur_paths->next;
}

int			optimize(t_map *map, t_room *rooms)
{
	int			optimize_try;
	t_paths		*cur_paths;

	map->min_lines = map->count_line;
	optimize_try = 3;
	map->is_best = 1;
	while (map->is_best == 1)
	{
		map->is_best = 0;
		cur_paths = map->best_paths;
		while (cur_paths != NULL && map->is_best == 0 && optimize_try-- != 0)
			take_paths_to_optimizate(cur_paths, map, rooms);
	}
	return (map->min_lines);
}
