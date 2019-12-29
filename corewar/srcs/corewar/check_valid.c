/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 15:39:43 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 16:15:58 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_one_register(t_vm_info *info, t_carriage *carr, int args[3])
{
	int i;
	int step;
	int reg;

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

int		check_registers(t_vm_info *info, t_carriage *carr)
{
	int types;
	int args[3];

	if (g_instr[carr->op_code - 1].args_types_code == 0)
		return (1);
	types = info->map[(carr->cur_pos + 1) % MEM_SIZE];
	args[0] = ((unsigned char)types & 0b11000000) / 64;
	args[1] = ((unsigned char)types & 0b110000) / 16;
	args[2] = ((unsigned char)types & 0b1100) / 4;
	return (check_one_register(info, carr, args));
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
