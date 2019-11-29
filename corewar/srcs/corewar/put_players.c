/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:06:18 by djast             #+#    #+#             */
/*   Updated: 2019/11/29 16:00:56 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		put_player(int pos, t_champ *player, t_vm_info *info)
{
	int index;

	index = 0;
	while (index != player->code_size)
	{
		info->map[pos + index] = player->code[index] & 0xFF;
		info->color_map[pos + index] = player->id;
		index++;
	}
}

void			place_players_on_arena(t_champ *champs, t_vm_info *info)
{
	int		place;
	t_champ	*cur_champ;

	place = 0;
	cur_champ = champs;
	while (place != info->count_players)
	{
		put_player(place * (MEM_SIZE / info->count_players), cur_champ,
																info);
		cur_champ = cur_champ->next;
		place++;
	}
}
