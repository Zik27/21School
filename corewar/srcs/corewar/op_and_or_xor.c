/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:18:50 by djast             #+#    #+#             */
/*   Updated: 2019/11/29 17:52:01 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_and(t_vm_info *info, t_carriage *carr)
{
	// ft_printf("and ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == IND_CODE)
		carr->args[0] = bytecode_to_int(info, carr->cur_pos +
									(carr->args[0] % IDX_MOD) % MEM_SIZE, 4);
	if (carr->args_types[1] == IND_CODE)
		carr->args[1] = bytecode_to_int(info, carr->cur_pos +
									(carr->args[1] % IDX_MOD) % MEM_SIZE, 4);
	if (carr->args_types[0] == REG_CODE)
		carr->args[0] = carr->registers[carr->args[0] - 1];
	if (carr->args_types[1] == REG_CODE)
		carr->args[1] = carr->registers[carr->args[1] - 1];
	carr->registers[carr->args[2] - 1] = carr->args[0] & carr->args[1];
	// ft_printf("%d %d r%d\n", carr->args[0], carr->args[1], carr->args[2]);
	if (carr->registers[carr->args[2] - 1] == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
	calc_jump_size(carr);
}

void	make_command_or(t_vm_info *info, t_carriage *carr)
{
	// ft_printf("or ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == IND_CODE)
		carr->args[0] = bytecode_to_int(info, carr->cur_pos +
									(carr->args[0] % IDX_MOD) % MEM_SIZE, 4);
	if (carr->args_types[1] == IND_CODE)
		carr->args[1] = bytecode_to_int(info, carr->cur_pos +
									(carr->args[1] % IDX_MOD) % MEM_SIZE, 4);
	if (carr->args_types[0] == REG_CODE)
		carr->args[0] = carr->registers[carr->args[0] - 1];
	if (carr->args_types[1] == REG_CODE)
		carr->args[1] = carr->registers[carr->args[1] - 1];
	carr->registers[carr->args[2] - 1] = carr->args[0] | carr->args[1];
	// ft_printf("%d %d r%d\n", carr->args[0], carr->args[1], carr->args[2]);
	if (carr->registers[carr->args[2] - 1] == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
	calc_jump_size(carr);
}

void	make_command_xor(t_vm_info *info, t_carriage *carr)
{
	// ft_printf("xor ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == IND_CODE)
		carr->args[0] = bytecode_to_int(info, carr->cur_pos +
									(carr->args[0] % IDX_MOD) % MEM_SIZE, 4);
	if (carr->args_types[1] == IND_CODE)
		carr->args[1] = bytecode_to_int(info, carr->cur_pos +
									(carr->args[1] % IDX_MOD) % MEM_SIZE, 4);
	if (carr->args_types[0] == REG_CODE)
		carr->args[0] = carr->registers[carr->args[0] - 1];
	if (carr->args_types[1] == REG_CODE)
		carr->args[1] = carr->registers[carr->args[1] - 1];
	// ft_printf("%d %d r%d\n", carr->args[0], carr->args[1], carr->args[2]);
	carr->registers[carr->args[2] - 1] = carr->args[0] ^ carr->args[1];
	if (carr->registers[carr->args[2] - 1] == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
	calc_jump_size(carr);
}
