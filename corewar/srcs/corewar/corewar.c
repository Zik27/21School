/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:11:12 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 16:15:52 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_die(t_vm_info *info)
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
			if (get_info_for_command(info, cur_carriage) == 1)
				make_command(info, champs, cur_carriage);
		cur_carriage->cur_pos = (cur_carriage->cur_pos +
										cur_carriage->jump_size) % MEM_SIZE;
		cur_carriage->jump_size = 0;
		cur_carriage = cur_carriage->next;
	}
	if (info->cycles_to_die <= 0 || info->cycles_after_check >=
												info->cycles_to_die)
		check_die(info);
	return (0);
}

int		no_sdl_loop(t_champ *champs, t_vm_info *info)
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
		return (-1);
	}
	info->cycle++;
	info->cycles_after_check++;
	if (info->carriages == NULL)
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
			info->last_live_player->id, info->last_live_player->name);
		return (-1);
	}
	return (0);
}

void	start_corewar(t_champ *champs, t_vm_info *info, t_sdl *sdl)
{
	int i;

	if (sdl != NULL)
		draw(sdl, info);
	while (1)
	{
		i = 0;
		if (sdl != NULL)
			sdl_loop(champs, info, sdl, &i);
		else
		{
			if (no_sdl_loop(champs, info) == -1)
				return ;
		}
	}
}

int		main(int argc, char **argv)
{
	t_champ		*champs;
	t_vm_info	*info;

	if (argc < 2)
		print_help(argv);
	info = (t_vm_info *)malloc(sizeof(t_vm_info));
	info->dump_cycle = -1;
	info->dump_type = -1;
	info->debug_flag = 0;
	info->champs = NULL;
	info->cur_champ = NULL;
	info->sdl = NULL;
	champs = parse_args(argc, argv, info);
	if (champs == NULL)
		cerror("No champions", NULL);
	if (get_player_count(champs) > MAX_PLAYERS)
		cerror("Too many champions", NULL);
	info = init_vm_info(&info, champs);
	place_players_on_arena(champs, info);
	info->carriages = init_carriages(champs, info);
	if (info->sdl == NULL)
		introducing(champs, info);
	start_corewar(champs, info, info->sdl);
	free_all(info->sdl, info, champs);
	return (0);
}
