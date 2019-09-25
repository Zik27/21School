/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:06:18 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 18:41:16 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		put_player(int pos, t_champ *player, char *map)
{
	int index;

	index = 0;
	while (index != player->code_size)
	{
		map[pos + index] = player->code[index] & 0xFF;
		index++;
	}
}

void			place_players_on_arena(t_champ *champs, t_vm_info *info)
{
	(void)champs;
	int place;
	t_champ *cur_champ;

	place = info->count_players - 1;
	cur_champ = champs;
	while (place != -1)
	{
		put_player(place * (MEM_SIZE / info->count_players), cur_champ,
																info->map);
		cur_champ = cur_champ->next;
		place--;
	}
}