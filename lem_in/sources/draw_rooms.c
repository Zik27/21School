/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:18:09 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 18:24:26 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void				draw_rectangle(t_room *cur_room, t_sdl *sdl)
{
	SDL_Rect	r;

	r.x = cur_room->x - ROOM_SIZE / 2;
	r.y = cur_room->y - ROOM_SIZE / 2;
	r.h = ROOM_SIZE;
	r.w = ROOM_SIZE;
	SDL_SetRenderDrawColor(sdl->renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(sdl->renderer, &r);
}

void				draw_rooms(t_sdl *sdl, t_room *rooms, t_map *map)
{
	t_room		*cur_room;
	SDL_Color	color;

	cur_room = rooms;
	color.b = 0;
	color.a = 255;
	while (cur_room != NULL)
	{
		draw_rectangle(cur_room, sdl);
		if (cur_room == map->start)
		{
			color.r = 0;
			color.g = 255;
			put_text(sdl, "Start", color, cur_room);
		}
		else if (cur_room == map->exit)
		{
			color.r = 255;
			color.g = 0;
			put_text(sdl, "End", color, cur_room);
		}
		cur_room = cur_room->next;
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
