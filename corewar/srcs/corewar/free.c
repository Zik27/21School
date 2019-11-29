/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:02:01 by djast             #+#    #+#             */
/*   Updated: 2019/11/22 17:31:31 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		free_cariages(t_carriage *carr)
{
	t_carriage *cur_carr;
	t_carriage *next_carr;

	if (carr == NULL)
		return ;
	cur_carr = carr;
	next_carr = cur_carr->next;
	while (cur_carr != NULL)
	{
		free(cur_carr->args_types);
		free(cur_carr->args);
		free(cur_carr);
		cur_carr = next_carr;
		if (next_carr != NULL)
			next_carr = next_carr->next;
	}
}

void			free_champions(t_champ *champs)
{
	t_champ *cur_champ;
	t_champ *next_champ;

	if (champs == NULL)
		return ;
	cur_champ = champs;
	next_champ = cur_champ->next;
	while (cur_champ != NULL)
	{
		free(cur_champ->name);
		free(cur_champ->comment);
		free(cur_champ->code);
		free(cur_champ);
		cur_champ = next_champ;
		if (next_champ != NULL)
			next_champ = next_champ->next;
	}
}

void			free_all(t_vm_info *info, t_champ *champs)
{
	free_cariages(info->carriages);
	free_champions(champs);
	free(info->map);
	free(info);
}
