/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:22:46 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 18:13:54 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_zjmp(t_vm_info *info, t_carriage *carr)
{
	printf("zjmp\n");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = DIR_CODE;
	get_op_arg(info, carr, carr->op_code);
	if (carr->carry == 1)
		carr->cur_pos += carr->args[0] % IDX_MOD;
}
