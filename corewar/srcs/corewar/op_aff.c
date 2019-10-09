/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:47:02 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 11:58:18 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_aff(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));

	carr->args_types[0] = REG_CODE;
	get_op_arg(info, carr, carr->op_code);
	ft_printf("%c", (char)carr->registers[carr->args[0] - 1]);
}