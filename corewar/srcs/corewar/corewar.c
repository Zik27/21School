/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:11:12 by djast             #+#    #+#             */
/*   Updated: 2019/09/26 17:49:03 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command(t_vm_info *info, t_carriage *carr)
{
	(void)info;
	(void)carr;

}

int		check_command_args(t_carriage *carr, int args[3])
{
	int cmd;

	cmd = carr->op_code;
	if ((g_instr[cmd - 1].args_types[0] & args[0]) != 0)
	{
		return (1);
	}
	return (0);
}

void	get_info_for_command(t_vm_info *info, t_carriage *carr)
{
	(void)info;
	(void)carr;
	char types;
	int		args[3];

	if (carr->op_code < 1 || carr->op_code > 16)
	{
		carr->cur_pos = (carr->cur_pos + 1) % MEM_SIZE;
		return ;
	}
	types = info->map[carr->cur_pos + 1];
	args[0] = ((unsigned char)types & 0b11000000) / 64;
	args[1] = ((unsigned char)types & 0b110000) / 16;
	args[2] = (unsigned char)types & 0b1100;
	if (check_command_args(carr, args) == 0)
	{
		return;
	}
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
			get_info_for_command(info, cur_carriage);
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

	if (argc < 2)
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