/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:25:42 by djast             #+#    #+#             */
/*   Updated: 2019/10/23 14:44:07 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			set_op_steps(t_carriage *carr)
{
	if (carr->op_code == 1 || carr->op_code == 4 || carr->op_code == 5
													|| carr->op_code == 13)
		carr->op_steps = 10;
	else if (carr->op_code == 2 || carr->op_code == 3)
		carr->op_steps = 5;
	else if (carr->op_code == 6 || carr->op_code == 7 || carr->op_code == 8)
		carr->op_steps = 6;
	else if (carr->op_code == 9)
		carr->op_steps = 20;
	else if (carr->op_code == 10 || carr->op_code == 11)
		carr->op_steps = 25;
	else if (carr->op_code == 12)
		carr->op_steps = 800;
	else if (carr->op_code == 14)
		carr->op_steps = 50;
	else if (carr->op_code == 15)
		carr->op_steps = 1000;
	else if (carr->op_code == 16)
		carr->op_steps = 2;
	else
	{
		carr->op_steps = 0;
		carr->cur_pos = (carr->cur_pos + 1) % MEM_SIZE;
	}
}

t_carriage		*init_carriages(t_champ *champs, t_vm_info *info)
{
	t_carriage	*carriages;
	t_carriage	*cur_carriage;
	t_carriage	*new_carriage;
	t_champ		*cur_player;

	cur_player = champs;
	carriages = NULL;
	while (cur_player != NULL)
	{
		new_carriage = init_carriage(cur_player, info);
		cur_carriage = carriages;
		carriages = new_carriage;
		carriages->next = cur_carriage;
		cur_player = cur_player->next;
	}
	return (carriages);
}

void			delete_carriage(t_vm_info *info, t_carriage *prev, t_carriage **cur, t_carriage *next)
{
	if (prev == NULL)
		info->carriages = next;
	else
		prev->next = next;
	free((*cur)->args_types);
	free((*cur)->args);
	free(*cur);
	*cur = prev;
}

void			delete_death_carr(t_vm_info *info, t_carriage *carr)
{
	t_carriage *prev_carr;
	t_carriage *cur_carr;
	t_carriage *next_carr;
	
	prev_carr = NULL;
	cur_carr = carr;
	if (carr != NULL)
		next_carr = cur_carr->next;
	while (cur_carr != NULL)
	{
		if (info->cycle - info->cycles_to_die > cur_carr->cycle_last_live)
			delete_carriage(info, prev_carr, &cur_carr, next_carr);
		prev_carr = cur_carr;
		if (cur_carr == NULL)
			cur_carr = info->carriages;
		else
			cur_carr = prev_carr->next;
		if (next_carr != NULL)
			next_carr = next_carr->next;
	}
}
