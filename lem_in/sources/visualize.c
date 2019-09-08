/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:46:56 by djast             #+#    #+#             */
/*   Updated: 2019/09/07 20:52:41 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_sdl		*create_window(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	sdl->window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, SIZE_WINDOW_X, SIZE_WINDOW_Y,
					SDL_WINDOW_OPENGL);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
											SDL_RENDERER_ACCELERATED);
	sdl->Sans = TTF_OpenFont("OpenSans.ttf", 500);
	SDL_SetWindowFullscreen(sdl->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	return (sdl);
}

void				put_text(t_sdl *sdl, char *message, SDL_Color color, t_room *cur_room)
{
	SDL_Rect	r;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sdl->Sans, message, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(sdl->renderer, surfaceMessage);
	r.x = cur_room->x - ROOM_SIZE / 2;
	r.y = cur_room->y - ROOM_SIZE - 5;
	r.h = 2 * ROOM_SIZE / 3;
	r.w = ROOM_SIZE;
	SDL_RenderCopy(sdl->renderer, Message, NULL, &r);
}

void				draw_rooms(t_sdl *sdl, t_room *rooms, t_map *map)
{
	t_room		*cur_room;
	SDL_Rect	r;
	SDL_Color	color;

	cur_room = rooms;
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);
	while (cur_room != NULL)
	{
		r.x = cur_room->x - ROOM_SIZE / 2;
		r.y = cur_room->y - ROOM_SIZE / 2;
		r.h = ROOM_SIZE;
		r.w = ROOM_SIZE;
		SDL_SetRenderDrawColor(sdl->renderer, 128, 128, 128, 255);
		SDL_RenderFillRect(sdl->renderer, &r);
		if (cur_room == map->start)
		{
			color.r = 0;
			color.g = 255;
			color.b = 0;
			color.a = 255;
			put_text(sdl, "Start", color, cur_room);
		}
		else if (cur_room == map->exit)
		{
			color.r = 255;
			color.g = 0;
			color.b = 0;
			color.a = 255;
			put_text(sdl, "End", color, cur_room);
		}
		cur_room = cur_room->next;
	}
}

void			draw_link(t_sdl *sdl, t_room *result1, t_room *result2, SDL_Color color)
{
    SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(sdl->renderer, result1->x, result1->y, result2->x, result2->y);
}

void			parse_link_and_draw_link(t_sdl *sdl, char *line, t_map *map)
{
	t_room	*result1;
	t_room	*result2;
	char	**ref;
	SDL_Color	color;

	ref = ft_strsplit(line, '-');
	result1 = find_room(ref[0], map->array_rooms, -1, map->count_rooms);
	result2 = find_room(ref[1], map->array_rooms, -1, map->count_rooms);
	color.r = 128;
	color.g = 128;
	color.b = 128;
	color.a = 255;
    draw_link(sdl, result1, result2, color);
}

void				highlight_paths(t_sdl *sdl, t_paths *paths, int path)
{
	t_paths *cur_path;
	t_path *cur_room;
	t_path *prev_room;
	SDL_Color	color;

	cur_path = paths;
	while (path--)
	{
		prev_room = cur_path->path;
		cur_room = prev_room->next;
		while (cur_room != NULL)
		{
			color.r = 0;
			color.g = 255;
			color.b = 0;
			color.a = 255;
			draw_link(sdl, prev_room->room_path, cur_room->room_path, color);
			prev_room = cur_room;
			cur_room = cur_room->next;
		}
		cur_path = cur_path->next;
	}
}

void				make_lem_in(t_sdl *sdl, t_map *map)
{
	char	*line;
	t_room	*rooms;
	int		count_rooms;
	t_file_txt	*input;
	t_paths *paths;
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
	draw_rooms(sdl, rooms, map);
	map->count_rooms = count_rooms;
	add_to_file_txt(&input, line);
	parse_links(&line, map);
	parse_link_and_draw_link(sdl, line, map);
	while (get_next_line(0, &line) == 1)
	{
		if (line && line[0] == '#')
			parse_comment(line, map);
		else if (line && ft_strchr(line, '-'))
		{
			parse_links(&line, map);
			parse_link_and_draw_link(sdl, line, map);
			
		}
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
	highlight_paths(sdl, paths, path);
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
	SDL_RenderPresent(sdl->renderer);
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