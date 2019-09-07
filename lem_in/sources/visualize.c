/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:46:56 by djast             #+#    #+#             */
/*   Updated: 2019/09/07 16:00:35 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_sdl		*create_window(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	SDL_Init(SDL_INIT_VIDEO);
	sdl->window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, SIZE_WINDOW_X, SIZE_WINDOW_Y,
					SDL_WINDOW_OPENGL);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
											SDL_RENDERER_ACCELERATED);
	SDL_SetWindowFullscreen(sdl->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	return (sdl);
}

void				draw_rooms(t_sdl *sdl, t_room *rooms)
{
	t_room *cur_room;
	SDL_Rect	r;

	cur_room = rooms;
	while (cur_room != NULL)
	{
		r.x = cur_room->x - ROOM_SIZE / 2;
		r.y = cur_room->y - ROOM_SIZE / 2;
		r.h = ROOM_SIZE;
		r.w = ROOM_SIZE;
		SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(sdl->renderer, &r);
		cur_room = cur_room->next;
	}
}

void				make_lem_in(t_sdl *sdl, t_map *map)
{
	char	*line;
	t_room	*rooms;
	int		count_rooms;
	t_file_txt	*input;

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

	draw_rooms(sdl, rooms);
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
}

void				pressed(int key)
{
	if (key == SDLK_ESCAPE)
		exit(0);
}

int					main()
{
	t_sdl		*sdl;
	SDL_Event	window_event;
	t_map	*map;

	sdl = create_window();

	map = init();
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