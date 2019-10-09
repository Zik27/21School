/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:25:42 by djast             #+#    #+#             */
/*   Updated: 2019/10/08 16:25:43 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			set_op_steps(t_carriage *carr)
{
	if (carr->op_code == 1 || carr->op_code == 4 || carr->op_code == 5
													|| carr->op_code == 13)
		carr->op_steps = 10;
	else if (carr->op_code == 2 || carr->op_code == 3)
		carr->op_steps = 2;
	else if (carr->op_code == 6 || carr->op_code == 7 || carr->op_code == 8)
		carr->op_steps = 6;
	else if (carr->op_code == 9)
		carr->op_steps = 20;
	else if (carr->op_code == 10 || carr->op_code == 11)
		carr->op_steps = 15;
	else if (carr->op_code == 12)
		carr->op_steps = 800;
	else if (carr->op_code == 14)
		carr->op_steps = 50;
	else if (carr->op_code == 15)
		carr->op_steps = 1000;
	else if (carr->op_code == 16)
		carr->op_steps = 2;
	else
		carr->op_steps = 0;
}

t_carriage		*init_carriages(t_champ *champs, t_vm_info *info)
{
	t_carriage	*carriages;
	t_carriage	*cur_carriage;
	t_carriage	*new_carriage;
	t_champ		*cur_player;
	int			id;

	cur_player = champs;
	carriages = NULL;
	id = info->count_players;
	
	while (cur_player != NULL)
	{
		//printf("cur_cur: %d\n", cur_player->id);
		new_carriage = init_carriage(id, cur_player, info);
		if (carriages == NULL)
		{
			carriages = new_carriage;
			cur_carriage = carriages;
		}
		else
		{
			cur_carriage->next = new_carriage;
			cur_carriage = cur_carriage->next;
		}
		cur_player = cur_player->next;
		id--;
	}
	return (carriages);
}
