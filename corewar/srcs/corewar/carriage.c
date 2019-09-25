/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:25:42 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 18:41:14 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
