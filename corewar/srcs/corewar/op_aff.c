/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:47:02 by djast             #+#    #+#             */
/*   Updated: 2019/11/29 10:28:33 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_aff(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));
	get_op_arg_type(info, carr);
	get_op_arg(info, carr, carr->op_code);
	ft_printf("Aff: %c\n", (char)carr->registers[carr->args[0] - 1]);
	calc_jump_size(carr);
}
