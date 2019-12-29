/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:21:36 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 13:17:51 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			make_command_lld(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == DIR_CODE)
		carr->registers[carr->args[1] - 1] = carr->args[0];
	else
		carr->registers[carr->args[1] - 1] = bytecode_to_int(info,
							(carr->cur_pos + carr->args[0]) % MEM_SIZE, 4);
	if (info->debug_flag == 1)
		ft_printf("lld %d r%d\n", carr->registers[carr->args[1] - 1],
															carr->args[1]);
	calc_jump_size(carr);
	if (carr->args[0] == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
}

static void		print_debug_lldi(t_vm_info *info, t_carriage *carr, int res)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (carr->args_types[0] == REG_CODE)
		a = carr->registers[carr->args[0] - 1];
	else if (carr->args_types[0] == DIR_CODE)
		a = carr->args[0];
	else if (carr->args_types[0] == IND_CODE)
		a = bytecode_to_int(info, (carr->cur_pos +
									(carr->args[0] % IDX_MOD)) % MEM_SIZE, 4);
	if (carr->args_types[1] == REG_CODE)
		b = carr->registers[carr->args[1] - 1];
	else if (carr->args_types[1] == DIR_CODE)
		b = carr->args[1];
	ft_printf("lldi %d %d r%d\n", a, b, carr->args[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
											a, b, res, carr->cur_pos + res);
}

void			make_command_lldi(t_vm_info *info, t_carriage *carr)
{
	int res;

	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	res = 0;
	if (carr->args_types[0] == REG_CODE)
		res += carr->registers[carr->args[0] - 1];
	else if (carr->args_types[0] == DIR_CODE)
		res += carr->args[0];
	else if (carr->args_types[0] == IND_CODE)
		res += bytecode_to_int(info, (carr->cur_pos +
									(carr->args[0] % IDX_MOD)) % MEM_SIZE, 4);
	if (carr->args_types[1] == REG_CODE)
		res += carr->registers[carr->args[1] - 1];
	else if (carr->args_types[1] == DIR_CODE)
		res += carr->args[1];
	if (info->debug_flag == 1)
		print_debug_lldi(info, carr, res);
	carr->registers[carr->args[2] - 1] = bytecode_to_int(info,
										(carr->cur_pos + res) % MEM_SIZE, 4);
	carr->carry = carr->registers[carr->args[2] - 1] == 0 ? 1 : 0;
	calc_jump_size(carr);
}
