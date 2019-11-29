/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:58:35 by djast             #+#    #+#             */
/*   Updated: 2019/11/22 17:35:15 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage			*init_carriage(t_champ *cur_player, t_vm_info *info)
{
	t_carriage	*new_carriage;
	int			i;
	static int	carr_id = 1;

	new_carriage = (t_carriage *)malloc(sizeof(t_carriage));
	new_carriage->id = carr_id;
	new_carriage->carry = 0;
	new_carriage->op_code = -1;
	new_carriage->cycle_last_live = -1;
	new_carriage->op_steps = 0;
	new_carriage->jump_size = 0;
	new_carriage->cur_pos = (carr_id++ - 1) * (MEM_SIZE / info->count_players);
	new_carriage->registers[0] = -cur_player->id;
	new_carriage->champ = cur_player;
	new_carriage->args_types = (int *)malloc(sizeof(int) * 3);
	new_carriage->args = (int *)malloc(sizeof(int) * 3);
	i = 1;
	while (i < REG_NUMBER)
		new_carriage->registers[i++] = 0;
	new_carriage->next = NULL;
	return (new_carriage);
}

t_vm_info			*init_vm_info(t_vm_info **info, t_champ *players)
{
	(*info)->count_players = get_player_count(players);
	(*info)->cycles_to_die = CYCLE_TO_DIE;
	(*info)->cycles_after_check = 1;
	(*info)->checks = 0;
	(*info)->cycle = 1;
	(*info)->live = 0;
	while (players->next != NULL)
		players = players->next;
	(*info)->last_live_player = players;
	(*info)->map = ft_strnew(MEM_SIZE);
	return (*info);
}

t_champ				*init_champ(int id)
{
	t_champ *champ;

	champ = (t_champ *)malloc(sizeof(t_champ));
	champ->id = id;
	champ->name = NULL;
	champ->comment = NULL;
	champ->code_size = -1;
	champ->code = NULL;
	champ->count_lives = 0;
	champ->last_live = 0;
	champ->next = NULL;
	return (champ);
}

t_sdl				*init_sdl()
{
	t_sdl *sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	sdl->window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, SIZE_WIN_X, 1300,
					SDL_WINDOW_OPENGL);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
					SDL_RENDERER_ACCELERATED);
	sdl->font = TTF_OpenFont("TNR.ttf", 16);
	sdl->speed = 40;
	return (sdl);
}
