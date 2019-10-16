/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:20:37 by djast             #+#    #+#             */
/*   Updated: 2019/10/16 16:13:38 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_command_live(t_vm_info *info, t_champ *champs, t_carriage *carr)
{
	t_champ *champ;

	ft_printf("live\n");
	ft_bzero(carr->args_types, 3 * sizeof(int));
	carr->args_types[0] = DIR_CODE;
	get_op_arg(info, carr, carr->op_code);
	printf("ADDR: %d\n", carr->args[0]);
	info->live++;
	carr->cycle_last_live = info->cycle;
	calc_jump_size(carr);
	if (carr->args[0] < 0 && carr->args[0] >= -info->count_players)
	{
		champ = find_player_by_id(champs, -carr->args[0]);
		champ->last_live = info->cycle;
		champ->count_lives++;
		info->last_live_player = champ;
	}
}
