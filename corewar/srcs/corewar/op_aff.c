/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:47:02 by djast             #+#    #+#             */
/*   Updated: 2019/11/22 15:51:12 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_aff(t_vm_info *info, t_carriage *carr)
{
	ft_bzero(carr->args_types, 3 * sizeof(int));

	get_op_arg_type(info, carr);
	// ft_printf("%d %d %d\n", carr->args_types[0], carr->args_types[1], carr->args_types[2]);
	get_op_arg(info, carr, carr->op_code);
	//ft_printf("Aff: %c\n", (char)carr->registers[carr->args[0] - 1]);
	calc_jump_size(carr);
	// ft_printf("%d\n", carr->jump_size);
}