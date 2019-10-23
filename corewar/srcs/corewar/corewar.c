/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:11:12 by djast             #+#    #+#             */
/*   Updated: 2019/10/23 17:02:45 by djast            ###   ########.fr       */
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
	else
		carr->cur_pos = (carr->cur_pos + 1) % MEM_SIZE;
}

void	make_command(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	(void) champs;
	if (carr->op_code > 0 && carr->op_code < 17)
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

	types = info->map[(carr->cur_pos + 1) % MEM_SIZE];
	args[0] = ((unsigned char)types & 0b11000000) / 64;
	args[1] = ((unsigned char)types & 0b110000) / 16;
	args[2] = ((unsigned char)types & 0b1100) / 4;
	i = 0;
	step = 0;
	while (i < 3)
	{
		if (args[i] == REG_CODE)
		{
			reg = info->map[(carr->cur_pos + step + 1 + 1) % MEM_SIZE];
			//printf("REGISTER_CHECK: %d\n", reg);
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
		if (args[i] == REG_CODE)
			step += 1;
		else if (args[i] == DIR_CODE)
			step += g_instr[carr->op_code - 1].t_dir_size;
		else if (args[i] == IND_CODE)
			step += 2;
		i++;
	}
	carr->cur_pos = (carr->cur_pos + step) % MEM_SIZE;
}

int		get_info_for_command(t_vm_info *info, t_carriage *carr)
{
	char	types;
	int		args[3];

	types = info->map[(carr->cur_pos + 1) % MEM_SIZE];
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

	if (info->cycles_to_die <= 0 || info->cycles_after_check >= info->cycles_to_die)
	{
		//ft_printf("DEAD\n");
		if (check_cycle_to_die(info) == 1)
			return (1);
		if (info->live >= NBR_LIVE)
		{
			info->checks = 0;
			info->cycles_after_check = 0;
			info->cycles_to_die -= CYCLE_DELTA;
		//	ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
		}
		else
		{
			info->checks++;
		//	printf("CHECKS: %d\n", info->checks);
			info->cycles_after_check = 0;
		}
		if (info->checks >= MAX_CHECKS)
		{
			info->checks = 0;
			info->cycles_after_check = 0;
			info->cycles_to_die -= CYCLE_DELTA;
		}
		info->live = 0;
	//	print_carriages(info->carriages);
	//	ft_printf("\n\n");
	}
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
		//printf("jump: %d\n", cur_carriage->jump_size);
		cur_carriage->cur_pos = (cur_carriage->cur_pos + cur_carriage->jump_size) % MEM_SIZE;
		cur_carriage->jump_size = 0;
		cur_carriage = cur_carriage->next;
	}
	return (0);
}

void	start_corewar(t_champ *champs, t_vm_info *info)
{
	(void) champs;
	
	//print_map(info->map);
	// print_carriages(info->carriages);
	// printf("\n\n");
	while (1)
	{
		//ft_printf("b: %p\n", champs->comment);
		// print_map(info->map);
		ft_printf("It is now cycle %d, %d\n", info->cycle, info->cycles_after_check);
		//ft_printf("%p", info->carriages->args);
		if (make_step_cycle(info, champs) == 1)
			return ;
		if (info->cycle == 5622)
		{
			print_map(info->map);
			// print_carriages(info->carriages);
			// ft_printf("\n\n");
		}
		//ft_printf("It is now cycle before %d\n", info->cycle);
		info->cycle++;
		//ft_printf("It is now cycle after %d\n", info->cycle);
		info->cycles_after_check++;
		// if (info->cycle == 3569)
		//  	break ;
	}
	//print_map(info->map);
}


int		main(int argc, char **argv)
{
	t_champ		*champs;
	t_vm_info	*info;

	if (argc < 2 || argc > 5)
	{
		print_help(argv);
		return (0);
	}
	champs = parse_args(argc, argv);
	info = init_vm_info(champs);
	place_players_on_arena(champs, info);
	info->carriages = init_carriages(champs, info);
	introducing(champs, info);
	start_corewar(champs, info);
	//free_all(info, champs);
	return (0);
}