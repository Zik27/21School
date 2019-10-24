/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:22:05 by djast             #+#    #+#             */
/*   Updated: 2019/10/24 15:06:54 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			make_command_st(t_vm_info *info, t_carriage *carr)
{
	ft_printf("st ");

	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	//printf("pos: %d\n", carr->cur_pos);
	get_op_arg(info, carr, carr->op_code);
	ft_printf("r%d %d\n", carr->args[0], carr->args[1]);
	if (carr->args_types[1] == REG_CODE)
		carr->registers[carr->args[1] - 1] = carr->registers[carr->args[0] - 1];
	else
		rewrite(info, (carr->cur_pos + (carr->args[1] % IDX_MOD)) % MEM_SIZE, carr->registers[carr->args[0] - 1]);
	calc_jump_size(carr);
}

static void		print_debug_sti(t_vm_info *info, t_carriage *carr, int res)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (carr->args_types[1] == REG_CODE)
		a = carr->registers[carr->args[1] - 1];
	else if (carr->args_types[1] == DIR_CODE)
		a = carr->args[1];
	else if (carr->args_types[1] == IND_CODE)
		a = bytecode_to_int((unsigned char *)(info->map + (carr->cur_pos + (carr->args[0] % IDX_MOD)) % MEM_SIZE), 4);
	if (carr->args_types[2] == REG_CODE)
		b = carr->registers[carr->args[2] - 1];
	else if (carr->args_types[2] == DIR_CODE)
		b = carr->args[2];

	ft_printf(" %d %d\n", a, b);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", a, b, res, carr->cur_pos + res);
}

void			make_command_sti(t_vm_info *info, t_carriage *carr)
{
	int res;

	ft_printf("sti ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	//printf("pos: %d\n", carr->cur_pos);
	//printf("%d %d %d\n", carr->args_types[0], carr->args_types[1], carr->args_types[2]);
	get_op_arg(info, carr, carr->op_code);
	//printf("args: %x %x\n", carr->args[0], carr->args[1]);
	res = 0;
	ft_printf("r%d ", carr->args_types[0]);
	if (carr->args_types[1] == REG_CODE)
		res += carr->registers[carr->args[1] - 1];
	else if (carr->args_types[1] == DIR_CODE)
		res += carr->args[1];
	else if (carr->args_types[1] == IND_CODE)
		res += bytecode_to_int((unsigned char *)(info->map + (carr->cur_pos + (carr->args[0] % IDX_MOD)) % MEM_SIZE), 4);
	if (carr->args_types[2] == REG_CODE)
		res += carr->registers[carr->args[2] - 1];
	else if (carr->args_types[2] == DIR_CODE)
		res += carr->args[2];
	print_debug_sti(info, carr, res);
	rewrite(info, (carr->cur_pos + (res % IDX_MOD)) % MEM_SIZE, carr->registers[carr->args[0] - 1]);
	calc_jump_size(carr);
}