/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:22:46 by djast             #+#    #+#             */
/*   Updated: 2019/10/16 19:03:37 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_zjmp(t_vm_info *info, t_carriage *carr)
{
	ft_printf("zjmp ");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = DIR_CODE;
	get_op_arg(info, carr, carr->op_code);
	ft_printf("%d ", carr->args[0]);
	if (carr->carry == 1)
	{
		ft_printf("OK\n");
		carr->cur_pos = (carr->cur_pos + carr->args[0] % IDX_MOD) % MEM_SIZE;
		if (carr->cur_pos < 0)
			carr->cur_pos = MEM_SIZE + carr->cur_pos;
	}
	else
	{
		ft_printf("FAILED\n");
		calc_jump_size(carr);
	}
}
