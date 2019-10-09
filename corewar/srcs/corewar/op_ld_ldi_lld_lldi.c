/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld_ldi_lld_lldi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:21:36 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 09:21:46 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_ld(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	(void) champs;

	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	//printf("pos: %d\n", carr->cur_pos);
	//printf("%d %d %d\n", carr->args_types[0], carr->args_types[1], carr->args_types[2]);
	get_op_arg(info, carr, carr->op_code);
	//printf("args: %x %x\n", carr->args[0], carr->args[1]);
	if (carr->args_types[0] == DIR_CODE)
		carr->registers[carr->args[1] - 1] = carr->args[0];
	else
		carr->registers[carr->args[1] - 1] = bytecode_to_int((unsigned char *)(info->map + carr->cur_pos + (carr->args[0] % IDX_MOD)), 4);
	calc_jump_size(carr);
	if (carr->args[0] == 0)
		carr->carry = 1;
	else
		carr->carry = 0;
}