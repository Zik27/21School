/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:13:08 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 09:23:20 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_op_arg_type(t_vm_info *info, t_carriage *carr)
{
	int types;

	types = info->map[carr->cur_pos + 1];
	carr->args_types[0] = ((unsigned char)types & 0b11000000) / 64;
	carr->args_types[1] = ((unsigned char)types & 0b110000) / 16;
	carr->args_types[2] = (unsigned char)types & 0b1100 / 4;
}

static void		get_op_arg(t_vm_info *info, t_carriage *carr, int cmd)
{
	int i;

	i = 0;
	carr->cur_step = 0;
	while (i < 3)
	{
		if (carr->args_types[i] == REG_CODE)
		{
			carr->args[i] = info->map[carr->cur_pos + carr->cur_step + 1 + 1];
			carr->cur_step += 1;
		}
		else if (carr->args_types[i] == DIR_CODE)
		{
			carr->args[i] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + 1 + g_instr[cmd - 1].args_types_code + carr->cur_step), g_instr[cmd - 1].t_dir_size);
			carr->cur_step += g_instr[cmd - 1].t_dir_size;
		}
		else if (carr->args_types[i] == IND_CODE)
		{
			carr->args[i] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + 1 + g_instr[cmd - 1].args_types_code + carr->cur_step), 2);
			carr->cur_step += 2;
		}
		i++;
	}
}

static void		calc_jump_size(t_carriage *carr)
{
	int i;

	i = 0;
	carr->jump_size = 1 + g_instr[carr->op_code - 1].args_types_code;
	while (i < 3)
	{
		if (carr->args_types[i] == REG_CODE)
			carr->jump_size += 1;
		else if (carr->args_types[i] == DIR_CODE)
			carr->jump_size += g_instr[carr->op_code - 1].t_dir_size;
		else if (carr->args_types[i] == IND_CODE)
			carr->jump_size += 2;
		i++;
	}
}
