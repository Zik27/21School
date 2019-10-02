/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:13:08 by djast             #+#    #+#             */
/*   Updated: 2019/10/02 18:12:50 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// static void		get_op_arg_type(t_vm_info *info, t_carriage *carr)
// {
// 	int types;
// 	types = info->map[carr->cur_pos + 1];
// 	carr->args_types[0] = ((unsigned char)types & 0b11000000) / 64;
// 	carr->args_types[1] = ((unsigned char)types & 0b110000) / 16;
// 	carr->args_types[2] = (unsigned char)types & 0b1100 / 4;
// }

static void		get_op_arg(t_vm_info *info, t_carriage *carr, int cmd)
{
	int i;

	i = 0;

	while (i < 3)
	{
		if (carr->args_types[i] == REG_CODE)
			carr->args[i] = info->map[carr->cur_pos + 1 + 1];
		else if (carr->args_types[i] == DIR_CODE)
			carr->args[i] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + 1), g_instr[cmd - 1].t_dir_size);
		else if (carr->args_types[i] == IND_CODE)
			carr->args[i] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + 1), 2);
		i++;
	}
}

void	make_command_live(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	t_champ *champ;

	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = DIR_CODE;
	get_op_arg(info, carr, carr->op_code);
	//printf("ADDR: %d\n", carr->args[0]);
	info->live++;
	carr->cycle_last_live = info->cycle;
	carr->jump_size = 5;
	if (carr->args[0] < 0 && carr->args[0] >= -info->count_players)
	{
		champ = find_player_by_id(champs, -carr->args[0]);
		champ->last_live = info->cycle;
		champ->count_lives++;
		info->last_live_player = champ;
	}
}
