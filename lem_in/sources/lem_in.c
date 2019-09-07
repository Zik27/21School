/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:18:55 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/07 16:04:12 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int		compare_steps(int ants, int steps, int count_paths, int *least_steps)
{
	int	tmp;

	if ((steps + ants - count_paths) % count_paths == 0)
		tmp = (steps + ants - count_paths) / count_paths;
	else
		tmp = (steps + ants - count_paths) / count_paths + 1;
	if (tmp < *least_steps)
	{
		*least_steps = tmp;
		return (1);
	}
	return (0);

}

int		get_steps(t_paths *paths, int count_paths)
{
	int	size;

	size = 0;
	while (count_paths--)
	{
		if (!paths)
			return (0);
		else
			size += paths->size;
		paths = paths->next;
	}
	return (size);
}

int		choose_path(int ants, t_paths *paths)
{
	int	count_paths;
	int	steps;
	int min_steps;

	count_paths = 1;
	min_steps = INT_MAX;
	while ((steps = get_steps(paths, count_paths)) != 0)
	{
		if (compare_steps(ants, steps, count_paths, &min_steps) == 0)
			break;
		count_paths++;
	}
	return (count_paths - 1);
}

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
	path = choose_path(map->count_ants, paths);
	printf("PATHS: %d\n", path);
	// while (input)
	// {
	// 	printf("AAA == %s\n", input->text);
	// 	input = input->next;
	// }

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