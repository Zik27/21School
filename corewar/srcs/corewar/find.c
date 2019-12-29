/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 15:29:26 by vurrigon          #+#    #+#             */
/*   Updated: 2019/12/29 15:30:18 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*find_player_by_id(t_champ *champs, int id)
{
	t_champ		*cur_champ;

	cur_champ = champs;
	while (cur_champ != NULL)
	{
		if (cur_champ->id == id)
			return (cur_champ);
		cur_champ = cur_champ->next;
	}
	return (NULL);
}
