/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 15:41:09 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	reading_links(char *line, t_map *map, t_room *rooms, int count_rooms)
{
	if (!rooms->x && !rooms->y && !rooms->name)
		error("Invalid input");
	list_to_array(map, rooms, count_rooms);
	sort_array_by_name(&map, count_rooms);
	map->count_rooms = count_rooms;
	add_to_file_txt(&map->input, line);
	parse_links(&line, map);
	while (get_next_line(0, &line) == 1)
	{
		if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, '-'))
			parse_links(&line, map);
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
}

void	parse(t_map *map)
{
	char		*line;
	t_room		*rooms;
	int			count_rooms;
	int			path;
	int			min_lines;
	t_paths		*best_paths;
	int			best_path_count;
	t_paths		*cur_paths;
	t_path		*cur_path;
	int			is_best;
	int			optimize_try;
	t_paths		*paths;

	count_rooms = 0;
	rooms = init_room(NULL, 0, 0);
	map->input = init_input_file(NULL);
	while (get_next_line(0, &line) == 1)
	{
		if (map->count_ants == 0)
			count_ants(line, map);
		else if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, ' '))
		{
			parse_rooms(line, map, &rooms);
			count_rooms++;
		}
		else if (line && ft_strchr(line, '-'))
		{
			reading_links(line, map, rooms, count_rooms);
			break ;
		}
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
	if (!map->start || !map->exit || map->has_links != 1)
		error("Invalid input");
	reverse_input_file(&map->input);
	best_paths = get_all_paths(map, rooms, 1);
	reverse_paths(&best_paths);
	best_path_count = choose_path(map->count_ants, best_paths, map);
	min_lines = map->count_out_line;
	optimize_try = 3;
	is_best = 1;
	while (is_best == 1)
	{
		is_best = 0;
		cur_paths = best_paths;
		while (cur_paths != NULL && is_best == 0 && optimize_try-- != 0)
		{
			cur_path = cur_paths->path;
			while (cur_path->next != NULL && is_best == 0)
			{
				delete_link(&(cur_path->room_path), cur_path->next->room_path);
				delete_link(&(cur_path->next->room_path), cur_path->room_path);
				paths = get_all_paths(map, rooms, 0);
				reverse_paths(&paths);
				path = choose_path(map->count_ants, paths, map);
				create_link(cur_path->room_path, cur_path->next->room_path);
				create_link(cur_path->next->room_path, cur_path->room_path);
				if (min_lines > map->count_out_line)
				{
					free_paths(best_paths);
					best_paths = paths;
					min_lines = map->count_out_line;
					best_path_count = path;
					is_best = 1;
					break ;
				}
				else
					free_paths(paths);
				cur_path = cur_path->next;
			}
			cur_paths = cur_paths->next;
		}
	}
	path_removal(best_paths, best_path_count);
	print_out(map->input, best_paths, map->count_ants, min_lines);
	free_input(map->input);
	free_rooms(rooms);
	free_paths(best_paths);
	free_map(map);
}

int		main(void)
{
	t_map	*map;

	map = init();
	parse(map);
	return (0);
}
