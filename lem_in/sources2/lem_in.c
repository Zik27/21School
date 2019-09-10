/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/08 13:55:27 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	parse(t_map *map)
{
	t_paths *paths;
	char	*line;
	t_room	*rooms;
	int		count_rooms;
	t_file_txt	*input;
	int			path;

	count_rooms = 0;
	rooms = init_room(NULL, 0, 0);
	input = init_input_file(NULL);
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
			break ;
		else
			error("Invalid input");
		add_to_file_txt(&input, line);
		//free(line);
	}
	if (!rooms->x && !rooms->y && !rooms->name)
		error("Invalid input");
	list_to_array(map, rooms, count_rooms);
	sort_array_by_name(&map, count_rooms);
	map->count_rooms = count_rooms;
	add_to_file_txt(&input, line);
	parse_links(&line, map);
	while (get_next_line(0, &line) == 1)
	{
		if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, '-'))
			parse_links(&line, map);
		else
			error("Invalid input");
		add_to_file_txt(&input, line);
		//free(line);
	}

	reverse_input_file(&input);

	bfs(map);

	paths = get_all_paths(map);
	reverse_paths(&paths);
	path = choose_path(map->count_ants, paths, map);
	printf("PATHS: %d\n", path);
	path_removal(paths, path);
	print_out(input, paths, map->count_ants, map->count_out_line);

	// printf("RESULT:\n");
	// while (rooms)
	// {
	// 	printf("%s x=%d y=%d path_len=%d\n", rooms->name, rooms->x, rooms->y, rooms->path_len);	
	// 	rooms = rooms->next;
	// }
	// 	t_link	*link;
	// 	link = rooms->links;

	// 	while (link)
	// 	{
	// 		printf("LINK === %s\n", link->room_l->name);
	// 		link = link->next;
	// 	}
	// 	rooms = rooms->next;
	// }
	// printf("START = %s, END = %s\n", map->start->name, map->exit->name);


	if (!map->start || !map->exit || map->has_links != 1)
		error("Invalid input");
	free_map(map);
	free_rooms(rooms);
}

int	main(void)
{
	t_map	*map;

	map = init();
	parse(map);
	return (0);
}