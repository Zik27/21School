/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:18:50 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 17:48:53 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_and(t_vm_info *info, t_carriage *carr)
{
	printf("and\n");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == IND_CODE)
		carr->args[0] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == IND_CODE)
		carr->args[1] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[1] % IDX_MOD)), 4);
	carr->registers[carr->args[2] - 1] = carr->args[0] & carr->args[1];
	calc_jump_size(carr);
}

void	make_command_or(t_vm_info *info, t_carriage *carr)
{
	printf("or\n");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == IND_CODE)
		carr->args[0] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == IND_CODE)
		carr->args[1] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[1] % IDX_MOD)), 4);
	carr->registers[carr->args[2] - 1] = carr->args[0] | carr->args[1];
	calc_jump_size(carr);
}

void	make_command_xor(t_vm_info *info, t_carriage *carr)
{
	printf("xor\n");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	if (carr->args_types[0] == IND_CODE)
		carr->args[0] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == IND_CODE)
		carr->args[1] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[1] % IDX_MOD)), 4);
	carr->registers[carr->args[2] - 1] = carr->args[0] ^ carr->args[1];
	calc_jump_size(carr);
}
