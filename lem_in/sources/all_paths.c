/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:33:10 by djast             #+#    #+#             */
/*   Updated: 2019/09/10 11:25:07 by djast            ###   ########.fr       */
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


static t_path		*get_one_path(t_map *map)
{
	t_room	*cur_room;
	t_link	*cur_link;
	t_path	*path;
	int		min_steps;

	path = NULL;
	cur_room = map->exit;
	path = add_to_path(path, map->exit);
	cur_link = cur_room->links;
	min_steps = cur_room->path_len - 1;
	while (min_steps != -1)
	{
		cur_link = cur_room->links;
		while (cur_link != NULL)
		{
			if (cur_link->room_l->path_len == min_steps)
			{
				cur_link->room_l->in_path = 1;
				path = add_to_path(path, cur_link->room_l);
				min_steps -= 1;
				cur_room = cur_link->room_l;
				break ;
			}
			else
				cur_link = cur_link->next;
		}
	}
	return (path);
}

// static int			check_links(t_room *cur_room)
// {
// 	t_link	*cur_link;

// 	cur_link = cur_room->links;
// 	while (cur_link != NULL)
// 	{
// 		if (cur_link->room_l->in_path == 0)
// 			return (1);
// 		cur_link = cur_link->next;
// 	}
// 	return (0);
// }

void			print_paths(t_paths *paths)
{
	t_link	*cur_link;
	t_path *cur_path;
	t_paths *cur_paths;

	cur_link = cur_room->links;
	while (cur_link != NULL)
	cur_paths = paths;
	while (cur_paths != NULL )
	{
		if (cur_link->room_l->in_path == 0)
			return (1);
		cur_link = cur_link->next;
		cur_path = cur_paths->path;
		printf("SIZE == %d\n", cur_paths->size);
		while (cur_path != NULL)
		{
			printf("%s -> ", cur_path->room_path->name);
			cur_path = cur_path->next;
		}
		printf("\n");
		cur_paths = cur_paths->next;
	}
	return (0);
	printf("__________________________\n");
}


// static int has_start(t_path *path, t_map *map)
// {
// 	if (path == NULL)
// 		return (-1);
// 	if (ft_strcmp(path->room_path->name, map->start->name) == 0)
// 		return (1);
// 	else if (ft_strcmp(path->room_path->name, map->exit->name) == 0)
// 		return (-1);
// 	return (0);
// }

t_paths				*get_all_paths(t_map *map, t_room *rooms, int status)
{
	t_paths	*paths;
	t_path	*path;
	int		status;

	paths = NULL;
	clear_full(rooms);
	bfs(map);
	if (map->exit->path_len == -1 && status == 1)
		error("No path found");
	while (map->exit->path_len != -1)
	{
		path = get_one_path(map);
		paths = add_to_paths(paths, path);	
		paths->size = map->exit->path_len;
		clear_bfs(rooms);
		bfs(map);
	}
	//print_paths(paths);
	return (paths);
}
// 	int		steps;
// 	t_paths	*paths;
// 	t_path	*path;
// 	int		status;

// 	steps = 0;
// 	paths = NULL;
// 	status = 0;
// 	while (check_links(map->start) == 1 &&
// 			check_links(map->exit) == 1)
// 	{
// 		path = get_one_path(map, steps, status);
// 		if (path->room_path == map->start && path->next->room_path == map->exit && status == 0)
// 			status = 1;
// 		if (has_start(path, map) == 1)
// 		{
// 			paths = add_to_paths(paths, path);
// 			paths->size = steps + 1;
// 		}
// 		else if (has_start(path, map) == -1)
// 			steps++;
// 	}
// 	return (paths);
// }
