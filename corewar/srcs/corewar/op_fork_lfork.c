/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:40:38 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 12:31:08 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			make_command_fork(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = T_DIR;
	get_op_arg(info, carr, carr->op_code);
	create_carr_copy(info, carr);
	info->carriages->cur_pos = (carr->cur_pos + carr->args[0] % IDX_MOD) %
																	MEM_SIZE;
	if (info->debug_flag == 1)
		ft_printf("fork %d (%d)\n", carr->args[0], carr->cur_pos +
													carr->args[0] % IDX_MOD);
	while (info->carriages->cur_pos < 0)
		info->carriages->cur_pos = MEM_SIZE + info->carriages->cur_pos;
	set_op_steps(info->carriages);
	calc_jump_size(carr);
}

void			make_command_lfork(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = T_DIR;
	get_op_arg(info, carr, carr->op_code);
	create_carr_copy(info, carr);
	info->carriages->cur_pos = (carr->cur_pos + carr->args[0]) % MEM_SIZE;
	while (info->carriages->cur_pos < 0)
		info->carriages->cur_pos = MEM_SIZE + info->carriages->cur_pos;
	if (info->debug_flag == 1)
		ft_printf("lfork %d (%d)\n", carr->args[0], carr->cur_pos +
			carr->args[0]);
	set_op_steps(info->carriages);
	calc_jump_size(carr);
}
