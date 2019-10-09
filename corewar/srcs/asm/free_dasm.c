/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dasm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:16:35 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/09 13:43:04 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static void free_arg_dasm(t_args_dasm *dasm_arg)
{
	t_args_dasm	*tmp;

	while (dasm_arg)
	{
		tmp = dasm_arg;
		dasm_arg = dasm_arg->next;
		free(tmp->data);
		free(tmp);
	}
}

static void	free_instr_dasm(t_inst_dasm *dasm_ins)
{
	t_inst_dasm	*tmp;

	while (dasm_ins)
	{
		tmp = dasm_ins;
		free_arg_dasm(dasm_ins->args);
		dasm_ins = dasm_ins->next;
		free(tmp);
	}
}

void	free_dasm(t_dasm *dasm)
{
	if (dasm->name)
		free(dasm->name);
	if (dasm->comment)
		free(dasm->comment);
	if (dasm->full_name_file)
		free(dasm->full_name_file);
	if (dasm->instr)
		free_instr_dasm(dasm->instr);
	free(dasm);
}