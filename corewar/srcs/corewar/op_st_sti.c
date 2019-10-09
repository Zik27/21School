/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:22:05 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 09:22:26 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_st(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	(void) champs;

	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	//printf("pos: %d\n", carr->cur_pos);
	//printf("%d %d %d\n", carr->args_types[0], carr->args_types[1], carr->args_types[2]);
	get_op_arg(info, carr, carr->op_code);
	//printf("args: %x %x\n", carr->args[0], carr->args[1]);
	if (carr->args_types[1] == REG_CODE)
		carr->registers[carr->args[1] - 1] = carr->registers[carr->args[0] - 1];
	else
		rewrite(info, carr->cur_pos + (carr->args[1] % IDX_MOD), carr->registers[carr->args[0] - 1]);
	calc_jump_size(carr);
}
