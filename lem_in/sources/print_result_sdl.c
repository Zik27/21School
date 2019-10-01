/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_sdl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:25:16 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 18:25:44 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_to_ants(t_ants **ants, t_path *cur_path)
{
	t_ants	*tmp;

	if (!(*ants)->next && !(*ants)->cur_path)
	{
		(*ants)->cur_path = cur_path;
		(*ants)->x = cur_path->room_path->x;
		(*ants)->y = cur_path->room_path->y;
		(*ants)->speed_x = (cur_path->next->room_path->x
										- cur_path->room_path->x) / SPEED;
		(*ants)->speed_y = (cur_path->next->room_path->y
										- cur_path->room_path->y) / SPEED;
	}
	else
	{
		tmp = init_ants(cur_path);
		tmp->next = (*ants);
		(*ants) = tmp;
	}
}

static void		animate_ants(t_sdl *sdl, t_ants *ants)
{
	t_ants	*cur_ants;
	int		steps;

	steps = SPEED;
	while (steps--)
	{
		cur_ants = ants;
		while (cur_ants != NULL)
		{
			cur_ants->x += cur_ants->speed_x;
			cur_ants->y += cur_ants->speed_y;
			cur_ants = cur_ants->next;
		}
		redraw(sdl, ants);
	}
}

static void		set_ant_speed(t_ants *cur_ants)
{
	if (cur_ants->cur_path->next != NULL)
	{
		cur_ants->speed_x = (cur_ants->cur_path->next->room_path->x
							- cur_ants->cur_path->room_path->x) / SPEED;
		cur_ants->speed_y = (cur_ants->cur_path->next->room_path->y
							- cur_ants->cur_path->room_path->y) / SPEED;
	}
	else
	{
		cur_ants->speed_x = 0;
		cur_ants->speed_y = 0;
	}
}

static void		move_ants(t_sdl *sdl, t_ants *ants)
{
	t_ants	*cur_ants;
	t_ants	*prev_ants;

	animate_ants(sdl, ants);
	cur_ants = ants;
	prev_ants = NULL;
	while (cur_ants != NULL)
	{
		if (cur_ants->cur_path->next != NULL)
		{
			cur_ants->cur_path = cur_ants->cur_path->next;
			cur_ants->x = cur_ants->cur_path->room_path->x;
			cur_ants->y = cur_ants->cur_path->room_path->y;
			set_ant_speed(cur_ants);
		}
		prev_ants = cur_ants;
		cur_ants = cur_ants->next;
	}
}

void			step_by_step_sdl(t_sdl *sdl, t_paths *paths, t_map *map)
{
	t_paths		*w;
	t_path		*end;
	t_ants		*ants;

	ants = init_ants(NULL);
	w = paths;
	while (map->count_line--)
	{
		while (w)
		{
			if (map->count_ant - map->id >= 0 && map->count_line + 1 >= w->size)
			{
				add_to_ants(&ants, w->path);
				end = make_step(w->path->next, map->id++);
			}
			else
				end = make_step(w->path->next, -1);
			if (end)
				end->room_path->ant_id = -1;
			w = w->next;
		}
		move_ants(sdl, ants);
		w = paths;
	}
	free_ants(ants);
}
