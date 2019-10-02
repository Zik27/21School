/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:11:12 by djast             #+#    #+#             */
/*   Updated: 2019/10/02 15:07:44 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// void	make_command_next(t_vm_info *info, t_carriage *carr)
// {
// 	if (carr->op_code == 9)
// 		make_command_zjmp(info, carr);
// 	else if (carr->op_code == 10)
// 		make_command_ldi(info, carr);
// 	else if (carr->op_code == 11)
// 		make_command_sti(info, carr);
// 	else if (carr->op_code == 12)
// 		make_command_fork(info, carr);
// 	else if (carr->op_code == 13)
// 		make_command_lld(info, carr);
// 	else if (carr->op_code == 14)
// 		make_command_lldi(info, carr);
// 	else if (carr->op_code == 15)
// 		make_command_lfork(info, carr);
// 	else if (carr->op_code == 16)
// 		make_command_aff(info, carr);
// }

void	make_command(t_vm_info *info, t_carriage *carr)
{
	if (carr->op_code == 1)
		make_command_live(info, carr);
	// else if (carr->op_code == 2)
	// 	make_command_ld(info, carr);
	// else if (carr->op_code == 3)
	// 	make_command_st(info, carr);
	// else if (carr->op_code == 4)
	// 	make_command_add(info, carr);
	// else if (carr->op_code == 5)
	// 	make_command_sub(info, carr);
	// else if (carr->op_code == 6)
	// 	make_command_and(info, carr);
	// else if (carr->op_code == 7)
	// 	make_command_or(info, carr);
	// else if (carr->op_code == 8)
	// 	make_command_xor(info, carr);
	// else
	// 	make_command_next(info, carr);
}

int		check_command_args(t_carriage *carr, int args[3])
{
	int cmd;

	cmd = carr->op_code;
	if ((g_instr[cmd - 1].args_types[0] & args[0]) != 0 ||
			(g_instr[cmd - 1].args_types[1] & args[1]) != 0 ||
			(g_instr[cmd - 1].args_types[2] & args[2]) != 0)
	{
		return (0);
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
		if (args[i] == 1)
			step += 1;
		else if (args[i] == 2)
			step += g_instr[carr->op_code - 1].t_dir_size;
		else if (args[i] == 3)
			step += 2;
		i++;
	}
	carr->cur_pos = (carr->cur_pos + step) % MEM_SIZE;
}

int		get_info_for_command(t_vm_info *info, t_carriage *carr)
{
	char types;
	int		args[3];

	if (carr->op_code < 1 || carr->op_code > 16)
	{
		carr->cur_pos = (carr->cur_pos + 1) % MEM_SIZE;
		return 0;
	}
	types = info->map[carr->cur_pos + 1];
	args[0] = ((unsigned char)types & 0b11000000) / 64;
	args[1] = ((unsigned char)types & 0b110000) / 16;
	args[2] = (unsigned char)types & 0b1100;
	if (check_command_args(carr, args) == 0)
	{
		skip_command(carr, args);
		return (0);
	}
	return (1);
}

void	make_step_cycle(t_vm_info *info, t_carriage *carriages)
{
	t_carriage *cur_carriage;

	cur_carriage = carriages;
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
				make_command(info, cur_carriage);
		}
		cur_carriage = cur_carriage->next;
	}
}

void	start_corewar(t_champ *champs, t_vm_info *info, t_carriage *carriages)
{
	(void) champs;
	int i = 10;
	
	while (i-- != 0)
	{
		// print_carriages(carriages);
		// print_map(info->map);
		make_step_cycle(info, carriages);
		info->cycle++;
	}

}


int		main(int argc, char **argv)
{
	t_champ		*champs;
	t_vm_info	*info;
	t_carriage	*carriages;

	if (argc < 2 || argc > 5)
	{
		print_help(argv);
		return (0);
	}
	champs = parse_args(argc, argv);
	info = init_vm_info(champs);
	place_players_on_arena(champs, info);
	carriages = init_carriages(champs, info);
	introducing(champs, info);
	start_corewar(champs, info, carriages);
	return (0);
}