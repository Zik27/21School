/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:48:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/19 15:07:58 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	free_arg_asm(t_tokens **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]->data);
		free(args[i++]);
	}
	free(args);
}

static void	free_instr_asm(t_instr *instr)
{
	t_instr	*tmp;

	while (instr)
	{
		tmp = instr;
		free_arg_asm(instr->args);
		instr = instr->next;
		free(tmp->instr);
		free(tmp);
	}
}

static void	free_labels(t_label *labels)
{
	t_label *tmp;

	while (labels)
	{
		tmp = labels;
		labels = labels->next;
		free(tmp->l_name);
		free(tmp);
	}
}

void		free_asm(t_player *player)
{
	free(player->name);
	free(player->comment);
	free_instr_asm(player->instr);
	free_labels(player->labels);
	free(player->file_name);
	free(player);
}
