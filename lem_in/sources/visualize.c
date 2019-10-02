/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:46:56 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 19:33:34 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reading_links_sdl(t_sdl *sdl, char *line, t_map *map,
											t_room *rooms)
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

static void		reading_rooms_sdl(t_sdl *sdl, t_map *map, t_room **rooms)
{
	char		*line;

	map->count_rooms = 0;
	while (get_next_line(0, &line) == 1)
	{
		if (map->count_ant == 0)
			count_ants(line, map);
		else if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, ' '))
		{
			parse_rooms(line, map, rooms);
			map->count_rooms++;
		}
		else if (line && ft_strchr(line, '-'))
		{
			reading_links_sdl(sdl, line, map, *rooms);
			break ;
		}
		else
			error("Invalid input");
		add_to_file_txt(&map->input, line);
	}
	if (!map->start || !map->exit || map->has_links != 1)
		error("Invalid input");
}

void			make_lem_in(t_sdl *sdl, t_map *map)
{
	t_room		*rooms;

	rooms = init_room(NULL, 0, 0);
	map->input = init_input_file(NULL);
	reading_rooms_sdl(sdl, map, &rooms);
	sdl->rooms = rooms;
	reverse_input_file(&map->input);
	map->best_paths = get_all_paths_prepare(map, rooms, 1);
	reverse_paths(&(map->best_paths));
	map->best_path_count = choose_path(map->count_ant, map->best_paths, map);
	map->count_line = optimize(map, rooms);
	sdl->best_paths = map->best_paths;
	sdl->best_paths_count = map->best_path_count;
	sdl->map = map;
	redraw(sdl, NULL);
	path_removal(map->best_paths, map->best_path_count);
	step_by_step_sdl(sdl, map->best_paths, map);
	free_input(map->input);
	free_rooms(rooms);
	free_paths(map->best_paths);
	free_map(map);
	free_links(sdl->links);
}

int				main(void)
{
	t_sdl		*sdl;
	SDL_Event	window_event;
	t_map		*map;

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
