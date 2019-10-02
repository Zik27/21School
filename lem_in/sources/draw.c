/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:23:20 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 18:23:39 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				draw_link(t_sdl *sdl, t_room *room_start, t_room *room_end,
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
	free(ref[0]);
	free(ref[1]);
	free(ref);
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
