/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:46:56 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 15:57:37 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reading_links(t_sdl *sdl, char *line, t_map *map, t_room *rooms)
{
	t_links *links;

	if (!rooms->x && !rooms->y && !rooms->name)
		error("Invalid input");
	links = init_links(NULL, NULL);
	list_to_array(map, rooms, map->count_rooms);
	sort_array_by_name(&map, map->count_rooms);
	add_to_file_txt(&map->input, line);
	parse_links(&line, map);
	parse_link_and_add(line, map, &links);
	while (get_next_line(0, &line) == 1)
	{
		if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, '-'))
		{
			parse_links(&line, map);
			parse_link_and_add(line, map, &links);
		}
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
	sdl->links = links;
}

void				make_lem_in(t_sdl *sdl, t_map *map)
{
	char		*line;
	t_room		*rooms;
	int			path;
	int			min_lines;
	t_paths		*best_paths;
	int			best_path_count;
	t_paths		*cur_paths;
	t_path		*cur_path;
	int			is_best;
	int			optimize_try;
	t_paths 	*paths;

	map->count_rooms = 0;
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
			map->count_rooms++;
		}
		else if (line && ft_strchr(line, '-'))
		{
			reading_links(sdl, line, map, rooms);
			break ;
		}
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
	if (!map->start || !map->exit || map->has_links != 1)
		error("Invalid input");
	sdl->rooms = rooms;
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
					break;
				}
				else
					free_paths(paths);
				cur_path = cur_path->next;
			}
			cur_paths = cur_paths->next;
		}
	}
	sdl->best_paths = best_paths;
	sdl->best_paths_count = best_path_count;
	sdl->map = map;
	redraw(sdl, NULL);
	path_removal(best_paths, best_path_count);
	step_by_step_sdl(sdl, best_paths, map->count_ants, min_lines);
	free_input(map->input);
	free_rooms(rooms);
	free_paths(best_paths);
	free_map(map);
	free_links(sdl->links);
}

int					main()
{
	t_sdl		*sdl;
	SDL_Event	window_event;
	t_map	*map;

	sdl = create_window();
	map = init();
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);	
	make_lem_in(sdl, map);
	while (1)
	{
		if (SDL_PollEvent(&window_event))
		{
			if (SDL_QUIT == window_event.type)
				break ;
			else if (window_event.type == SDL_KEYDOWN)
				pressed(window_event.key.keysym.sym);
		}
	}
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	free(sdl);
	return (0);
}