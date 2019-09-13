/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_sdl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:25:16 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 15:59:03 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*make_step_sdl(t_path *path, int id)
{
	int		tmp;
	t_path	*end;

	end = NULL;
	if (path->room_path->ant_id == -1 && id != -1)
	{
		path->room_path->ant_id = id;
		if (!path->next)
			end = path;
	}
	else
	{
		tmp = path->room_path->ant_id;
		path->room_path->ant_id = id;
		path = path->next;
		while (path)
		{
			ft_swap(&tmp, &path->room_path->ant_id);
			if (id > 0 && tmp == -1)
				break ;
			if (!path->next)
				end = path;
			path = path->next;
		}
	}
	return (end);
}

static void		add_to_ants(t_ants **ants, t_path *cur_path)
{
	t_ants	*tmp;

	if (!(*ants)->next && !(*ants)->cur_path)
	{
		(*ants)->cur_path = cur_path;
		(*ants)->x = cur_path->room_path->x;
		(*ants)->y = cur_path->room_path->y;
		(*ants)->speed_x = (cur_path->next->room_path->x - cur_path->room_path->x) / SPEED;
		(*ants)->speed_y = (cur_path->next->room_path->y - cur_path->room_path->y) / SPEED;
	}
	else
	{
		tmp = init_ants(cur_path);
		tmp->next = (*ants);
		(*ants) = tmp;
	}
}

static void	animate_ants(t_sdl *sdl, t_ants *ants)
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

static void	move_ants(t_ants *ants)
{
	t_ants	*cur_ants;
	t_ants	*prev_ants;

	cur_ants = ants;
	prev_ants = NULL;
	while (cur_ants != NULL)
	{
		if (cur_ants->cur_path->next != NULL)
		{
			cur_ants->cur_path = cur_ants->cur_path->next;
			cur_ants->x = cur_ants->cur_path->room_path->x;
			cur_ants->y = cur_ants->cur_path->room_path->y;
			if (cur_ants->cur_path->next != NULL)
			{
				cur_ants->speed_x = (cur_ants->cur_path->next->room_path->x - cur_ants->cur_path->room_path->x) / SPEED;
				cur_ants->speed_y = (cur_ants->cur_path->next->room_path->y - cur_ants->cur_path->room_path->y) / SPEED;
			}
			else
			{
				cur_ants->speed_x = 0;
				cur_ants->speed_y = 0;
			}
		}
		prev_ants = cur_ants;
		cur_ants = cur_ants->next;
	}
}

void	step_by_step_sdl(t_sdl *sdl, t_paths *paths, int count_ants,
								int count_lines)
{
	int			id;
	t_paths		*ways;
	t_path		*end;
	t_ants		*ants;

	ants = init_ants(NULL);
	ways = paths;
	id = 1;
	while (count_lines)
	{
		while (ways)
		{
			if (count_ants - id >= 0 && count_lines >= ways->size)
			{
				add_to_ants(&ants, ways->path);
				end = make_step_sdl(ways->path->next, id++);
			}
			else
				end = make_step_sdl(ways->path->next, -1);
			if (end)
				end->room_path->ant_id = -1;
			ways = ways->next;
		}
		animate_ants(sdl, ants);
		move_ants(ants);
		count_lines--;
		ways = paths;
	}
	free_ants(ants);
}
