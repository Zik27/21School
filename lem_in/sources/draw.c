/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:23:20 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 15:37:43 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				draw_rooms(t_sdl *sdl, t_room *rooms, t_map *map)
{
	t_room		*cur_room;
	SDL_Rect	r;
	SDL_Color	color;

	cur_room = rooms;
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

static void			draw_link(t_sdl *sdl, t_room *room_start, t_room *room_end,
								SDL_Color color)
{
	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(sdl->renderer, room_start->x,
										room_start->y,
										room_end->x,
										room_end->y);
}

void				draw_links(t_sdl *sdl, t_links *links)
{
	SDL_Color color;

	color.r = 128;
	color.g = 128;
	color.b = 128;
	color.a = 255;
	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g, color.b, color.a);
	while (links != NULL)
	{
		SDL_RenderDrawLine(sdl->renderer, links->room_start->x,
											links->room_start->y,
											links->room_end->x,
											links->room_end->y);
		links = links->next;
	}
}

static void			add_to_links(t_links **links, t_room *room_start,
									t_room *room_end)
{
	t_links	*tmp;

	if (!(*links)->next && !(*links)->room_start && !(*links)->room_end)
	{
		(*links)->room_start = room_start;
		(*links)->room_end = room_end;
	}
	else
	{
		tmp = init_links(room_start, room_end);
		tmp->next = (*links);
		(*links) = tmp;
	}
}

void				parse_link_and_add(char *line, t_map *map, t_links **links)
{
	t_room	*result1;
	t_room	*result2;
	char	**ref;

	ref = ft_strsplit(line, '-');
	result1 = find_room(ref[0], map->array_rooms, -1, map->count_rooms);
	result2 = find_room(ref[1], map->array_rooms, -1, map->count_rooms);
	add_to_links(links, result1, result2);
}

void				highlight_paths(t_sdl *sdl, t_paths *paths, int path)
{
	t_paths		*cur_path;
	t_path		*cur_room;
	t_path		*prev_room;
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

void				draw_ants(t_sdl *sdl, t_ants *ants)
{
	t_ants		*cur_ants;
	SDL_Rect	r;

	cur_ants = ants;
	while (cur_ants != NULL)
	{
		r.x = cur_ants->x - ANTS_SIZE / 2;
		r.y = cur_ants->y - ANTS_SIZE / 2;
		r.h = ANTS_SIZE;
		r.w = ANTS_SIZE;
		SDL_RenderCopy(sdl->renderer, sdl->ant, NULL, &r);
		cur_ants = cur_ants->next;
	}
}

void				redraw(t_sdl *sdl, t_ants *ants)
{
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->background, NULL, NULL);
	draw_rooms(sdl, sdl->rooms, sdl->map);
	draw_links(sdl, sdl->links);
	highlight_paths(sdl, sdl->best_paths, sdl->best_paths_count);
	if (ants != NULL)
		draw_ants(sdl, ants);
	SDL_RenderPresent(sdl->renderer);
}
