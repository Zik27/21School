/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:11:12 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 20:26:51 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_next(t_vm_info *info, t_carriage *carr)
{
	if (carr->op_code == 9)
		make_command_zjmp(info, carr);
	else if (carr->op_code == 10)
		make_command_ldi(info, carr);
	else if (carr->op_code == 11)
		make_command_sti(info, carr);
	else if (carr->op_code == 12)
		make_command_fork(info, carr);
	else if (carr->op_code == 13)
		make_command_lld(info, carr);
	else if (carr->op_code == 14)
		make_command_lldi(info, carr);
	else if (carr->op_code == 15)
		make_command_lfork(info, carr);
	else if (carr->op_code == 16)
		make_command_aff(info, carr);
}

void	make_command(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	(void) champs;
	if (carr->op_code > 0 && carr->op_code < 16 && info->debug_flag == 1)
		ft_printf("P %4d | ", carr->id);
	if (carr->op_code == 1)
		make_command_live(info, champs, carr);
	else if (carr->op_code == 2)
	 	make_command_ld(info, carr);
	else if (carr->op_code == 3)
	 	make_command_st(info, carr);
	else if (carr->op_code == 4)
		make_command_add(info, carr);
	else if (carr->op_code == 5)
		make_command_sub(info, carr);
	else if (carr->op_code == 6)
		make_command_and(info, carr);
	else if (carr->op_code == 7)
		make_command_or(info, carr);
	else if (carr->op_code == 8)
		make_command_xor(info, carr);
	else
		make_command_next(info, carr);
}

int		check_registers(t_vm_info *info, t_carriage *carr)
{
	int i;
	int step;
	int reg;
	int types;
	int args[3];

	if (g_instr[carr->op_code - 1].args_types_code == 0)
		return (1);
	types = info->map[(carr->cur_pos + 1) % MEM_SIZE];
	args[0] = ((unsigned char)types & 0b11000000) / 64;
	args[1] = ((unsigned char)types & 0b110000) / 16;
	args[2] = ((unsigned char)types & 0b1100) / 4;
	i = 0;
	step = 0;
	while (i < 3)
	{
		if (g_instr[carr->op_code - 1].args_types[i] == 0)
			break ;
		if (args[i] == REG_CODE)
		{
			reg = info->map[(carr->cur_pos + step + 1 + 1) % MEM_SIZE];
			if (reg < 1 || reg > 16)
				return (0);
			step += 1;
		}
		else if (args[i] == DIR_CODE)
			step += g_instr[carr->op_code - 1].t_dir_size;
		else if (args[i] == IND_CODE)
			step += 2;
		i++;
	}
	return (1);
}

int		check_command_args(t_carriage *carr, int args[3])
{
	int cmd;
	int i;

	cmd = carr->op_code;
	if (g_instr[cmd - 1].args_types_code == 0)
		return (1);
	i = 0;
	while (i < 3)
	{
		if (args[i] == IND_CODE)
			args[i] += 1;
		if (g_instr[cmd - 1].args_types[i] == 0)
			return (1);
		if ((g_instr[cmd - 1].args_types[i] & args[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	skip_command(t_carriage *carr, int args[3])
{
	int step;
	int i;

	step = 2;
	i = 0;
	while (i < 3)
	{
		if (g_instr[carr->op_code - 1].args_types[i] == 0)
			break ;
		if (args[i] == REG_CODE)
			step += 1;
		else if (args[i] == DIR_CODE)
			step += g_instr[carr->op_code - 1].t_dir_size;
		else if (args[i] == IND_CODE || args[i] == T_IND)
			step += 2;
		i++;
	}
	carr->cur_pos = (carr->cur_pos + step) % MEM_SIZE;
}

int		get_info_for_command(t_vm_info *info, t_carriage *carr)
{
	char	types;
	int		args[3];

	if (carr->op_code < 1 || carr->op_code > 16)
    {
    	carr->cur_pos = (carr->cur_pos + 1) % MEM_SIZE;
        return (0);
    }
    types = (info->map[(carr->cur_pos + 1) % MEM_SIZE]) & 0xFF;
	args[0] = ((unsigned char)types & 0b11000000) / 64;
	args[1] = ((unsigned char)types & 0b110000) / 16;
	args[2] = ((unsigned char)types & 0b1100) / 4;
	if (check_command_args(carr, args) == 0 || check_registers(info, carr) == 0)
	{
		skip_command(carr, args);
		return (0);
	}
	return (1);
}

int		make_step_cycle(t_vm_info *info, t_champ *champs)
{
	t_carriage *cur_carriage;

	cur_carriage = info->carriages;
	while (cur_carriage != NULL)
	{
		if (cur_carriage->op_steps == 0)
		{
			cur_carriage->op_code = info->map[cur_carriage->cur_pos];
			set_op_steps(cur_carriage);
		}
		if (cur_carriage->op_steps > 0)
			cur_carriage->op_steps--;
		if (cur_carriage->op_steps == 0)
		{
			if (get_info_for_command(info, cur_carriage) == 1)
				make_command(info, champs, cur_carriage);
		}
		cur_carriage->cur_pos = (cur_carriage->cur_pos + cur_carriage->jump_size) % MEM_SIZE;
		cur_carriage->jump_size = 0;
		cur_carriage = cur_carriage->next;
	}
	if (info->cycles_to_die <= 0 || info->cycles_after_check >= info->cycles_to_die)
	{
		check_cycle_to_die(info);
		if (info->live >= NBR_LIVE)
		{
			info->checks = 0;
			info->cycles_after_check = 0;
			info->cycles_to_die -= CYCLE_DELTA;
			if (info->debug_flag == 1)
				ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
		}
		else
		{
			info->checks++;
			info->cycles_after_check = 0;
		}
		if (info->checks >= MAX_CHECKS)
		{
			info->checks = 0;
			info->cycles_after_check = 0;
			info->cycles_to_die -= CYCLE_DELTA;
			if (info->debug_flag == 1)
				ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
		}
		info->live = 0;
	}
	return (0);
}

void	start_corewar(t_champ *champs, t_vm_info *info, t_sdl *sdl)
{
	(void) champs;
	int i;
	if (sdl != NULL)
	{
		draw(sdl, info);
	}
	while (1)
	{
		i = 0;
		if (sdl != NULL)
		{
			while (i < sdl->speed && sdl->is_pause == 0)
			{
				if (make_step_cycle(info, champs) == 1)
					return ;
				info->cycle++;
				info->cycles_after_check++;
				i++;
				if (info->carriages == NULL)
				{
					SDL_DestroyWindow(sdl->window);
					SDL_Quit();
					return ;
				}
			}
			if (sdl->is_pause == 0)
				draw(sdl, info);
			if (SDL_PollEvent(&(sdl->window_event)))
			{
				if (SDL_QUIT == sdl->window_event.type)
					exit(0);
				else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_ESCAPE ==
							sdl->window_event.key.keysym.sym)
					exit(0);
				else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_SPACE ==
							sdl->window_event.key.keysym.sym)
				{
					sdl->is_pause = !sdl->is_pause;
				}
				else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_s ==
							sdl->window_event.key.keysym.sym && sdl->is_pause == 1)
				{
					if (make_step_cycle(info, champs) == 1)
						return ;
					info->cycle++;
					info->cycles_after_check++;
					i++;
					if (info->carriages == NULL)
					{
						SDL_DestroyWindow(sdl->window);
						SDL_Quit();
						return ;
					}
					draw(sdl, info);
				}
				else if(sdl->window_event.type == SDL_KEYDOWN && SDLK_r ==
							sdl->window_event.key.keysym.sym)
				{
					sdl->speed += 100;
					draw(sdl, info);
				}
				else if(sdl->window_event.type == SDL_KEYDOWN && SDLK_e ==
							sdl->window_event.key.keysym.sym)
				{
					sdl->speed += 10;
					draw(sdl, info);
				}
				else if(sdl->window_event.type == SDL_KEYDOWN && SDLK_w ==
							sdl->window_event.key.keysym.sym)
				{
					sdl->speed = sdl->speed > 9 ? sdl->speed - 10 : 0;
					draw(sdl, info);
				}
				else if(sdl->window_event.type == SDL_KEYDOWN && SDLK_q ==
							sdl->window_event.key.keysym.sym)
				{
					sdl->speed = sdl->speed > 99 ? sdl->speed - 100 : 0;
					draw(sdl, info);
				}
			}		
		}
		else
		{
			if (info->debug_flag == 1)
				ft_printf("It is now cycle %d\n", info->cycle);
			make_step_cycle(info, champs);
			if (info->dump_cycle == info->cycle)
			{
				if (info->dump_type == CODE_D)
					print_map(info->map, 64);
				else if (info->dump_type == CODE_DUMP)
					print_map(info->map, 32);
				break ;
			}
			info->cycle++;
			info->cycles_after_check++;
			if (info->carriages == NULL)
			{
				ft_printf("Contestant %d, \"%s\", has won !\n", info->last_live_player->id, info->last_live_player->name);
				return ;
			}
		}
	}
}

int		main(int argc, char **argv)
{
	t_champ		*champs;
	t_vm_info	*info;
	t_sdl		*sdl;

	sleep(8);
	if (argc < 2)
	{
		print_help(argv);
		return (0);
	}
	sdl = NULL;
	info = (t_vm_info *)malloc(sizeof(t_vm_info));
	info->dump_cycle = -1;
	info->dump_type = -1;
	info->debug_flag = 0;
	champs = parse_args(argc, argv, &sdl, info);
	if (champs == NULL)
		cerror("No champions", NULL);
	if (get_player_count(champs) > MAX_PLAYERS)
		cerror("Too many champions", NULL);
	info = init_vm_info(&info, champs);
	place_players_on_arena(champs, info);
	info->carriages = init_carriages(champs, info);
	if (sdl == NULL)
		introducing(champs, info);

	start_corewar(champs, info, sdl);
	free_all(sdl, info, champs);
	return (0);
}
