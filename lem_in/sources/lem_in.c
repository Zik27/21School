/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 18:46:14 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void		parse(t_map *map)
{
	t_room		*rooms;

	rooms = init_room(NULL, 0, 0);
	map->input = init_input_file(NULL);
	reading_rooms(map, &rooms);
	reverse_input_file(&map->input);
	map->best_paths = get_all_paths_prepare(map, rooms, 1);
	reverse_paths(&(map->best_paths));
	map->best_path_count = choose_path(map->count_ant, map->best_paths, map);
	map->count_line = optimize(map, rooms);
	path_removal(map->best_paths, map->best_path_count);
	print_out(map->input, map->best_paths, map->count_ant, map->count_line);
	free_input(map->input);
	free_rooms(rooms);
	free_paths(map->best_paths);
	free_map(map);
}

int			main(void)
{
	t_map	*map;

	map = init();
	parse(map);
	return (0);
}
