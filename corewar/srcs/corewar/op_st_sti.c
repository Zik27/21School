/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:22:05 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 18:33:03 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			make_command_st(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (info->debug_flag == 1)
		ft_printf("st r%d %d\n", carr->args[0], carr->args[1]);
	if (carr->args_types[1] == REG_CODE)
		carr->registers[carr->args[1] - 1] = carr->registers[carr->args[0] - 1];
	else
		rewrite(info, (carr->cur_pos + (carr->args[1] % IDX_MOD)) % MEM_SIZE,
							carr->registers[carr->args[0] - 1], carr->champ);
	calc_jump_size(carr);
}

static void		print_debug_sti(t_vm_info *info, t_carriage *carr, int res)
{
	int a;
	int b;
	int pc;

	a = 0;
	b = 0;
	if (carr->args_types[1] == REG_CODE)
		a = carr->registers[carr->args[1] - 1];
	else if (carr->args_types[1] == DIR_CODE)
		a = carr->args[1];
	else if (carr->args_types[1] == IND_CODE)
		a = bytecode_to_int(info, carr->cur_pos + (carr->args[1] % IDX_MOD), 4);
	if (carr->args_types[2] == REG_CODE)
		b = carr->registers[carr->args[2] - 1];
	else if (carr->args_types[2] == DIR_CODE)
		b = carr->args[2];
	ft_printf("sti r%d %d %d\n", carr->args[0], a, b);
	pc = carr->cur_pos + (res % IDX_MOD);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
																a, b, res, pc);
}

void			make_command_sti(t_vm_info *info, t_carriage *carr)
{
	int res;

	res = 0;
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[1] == REG_CODE)
		res += carr->registers[carr->args[1] - 1];
	else if (carr->args_types[1] == DIR_CODE)
		res += carr->args[1];
	else if (carr->args_types[1] == IND_CODE)
		res += bytecode_to_int(info, carr->cur_pos +
												(carr->args[1] % IDX_MOD), 4);
	if (carr->args_types[2] == REG_CODE)
		res += carr->registers[carr->args[2] - 1];
	else if (carr->args_types[2] == DIR_CODE)
		res += carr->args[2];
	if (info->debug_flag == 1)
		print_debug_sti(info, carr, res);
	rewrite(info, (carr->cur_pos + (res % IDX_MOD)) % MEM_SIZE,
							carr->registers[carr->args[0] - 1], carr->champ);
	calc_jump_size(carr);
}
