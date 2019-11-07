/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:40:38 by djast             #+#    #+#             */
/*   Updated: 2019/11/07 15:58:29 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			make_command_fork(t_vm_info *info, t_carriage *carr)
{
	ft_printf("fork ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = T_DIR;
	get_op_arg(info, carr, carr->op_code);
	create_carr_copy(info, carr);
	info->carriages->cur_pos = (carr->cur_pos + carr->args[0] % IDX_MOD) % MEM_SIZE;
	if (info->carriages->cur_pos < 0)
		info->carriages->cur_pos = 4096 + info->carriages->cur_pos;
	ft_printf("%d (%d)\n", carr->args[0], info->carriages->cur_pos);
	info->carriages->op_code = info->map[info->carriages->cur_pos];
	set_op_steps(info->carriages);	
	calc_jump_size(carr);
	
}

void			make_command_lfork(t_vm_info *info, t_carriage *carr)
{
	ft_printf("lfork ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = T_DIR;
	get_op_arg(info, carr, carr->op_code);
	create_carr_copy(info, carr);
	info->carriages->cur_pos = (carr->cur_pos + carr->args[0]) % MEM_SIZE;	
	info->carriages->op_code = info->map[info->carriages->cur_pos];
	ft_printf("%d (%d)\n", carr->args[0], carr->cur_pos + carr->args[0]);
	set_op_steps(info->carriages);	
	calc_jump_size(carr);
}