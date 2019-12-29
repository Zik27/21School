/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 15:38:39 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 15:39:17 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_next(t_vm_info *info, t_carriage *carr)
{
	if (carr->op_code == 9)
		make_command_zjmp(info, carr);
	else if (carr->op_code == 10)
		make_command_ldi(info, carr);
	else if (carr->op_code == 11)
		make_command_sti(info, carr);
	else if (carr->op_code == 12)
		make_command_fork(info, carr);
	else if (carr->op_code == 13)
		make_command_lld(info, carr);
	else if (carr->op_code == 14)
		make_command_lldi(info, carr);
	else if (carr->op_code == 15)
		make_command_lfork(info, carr);
	else if (carr->op_code == 16)
		make_command_aff(info, carr);
}

void	make_command(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	if (carr->op_code > 0 && carr->op_code < 16 && info->debug_flag == 1)
		ft_printf("P %4d | ", carr->id);
	if (carr->op_code == 1)
		make_command_live(info, champs, carr);
	else if (carr->op_code == 2)
		make_command_ld(info, carr);
	else if (carr->op_code == 3)
		make_command_st(info, carr);
	else if (carr->op_code == 4)
		make_command_add(info, carr);
	else if (carr->op_code == 5)
		make_command_sub(info, carr);
	else if (carr->op_code == 6)
		make_command_and(info, carr);
	else if (carr->op_code == 7)
		make_command_or(info, carr);
	else if (carr->op_code == 8)
		make_command_xor(info, carr);
	else
		make_command_next(info, carr);
}
