/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dasm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:13:53 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/01 11:15:54 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

t_dasm	*init_dasm(char	*full_name)
{
	t_dasm *dasm;

	if (!(dasm = malloc(sizeof(t_dasm))))
		return (NULL);
	dasm->name = NULL;
	dasm->comment = NULL;
	dasm->size = 0;
	dasm->full_name_file = full_name;
	dasm->arg_types = NULL;
	dasm->instr = NULL;
	return (dasm);
}

t_inst_dasm	*init_ins_dasm(char *name)
{
	t_inst_dasm *op;
	if (!(op = malloc(sizeof(t_inst_dasm))))
		return (NULL);
	op->name = name;
	op->args = NULL;
	op->next = NULL;
	return (op);
}

t_args_dasm	*init_arg(char *name)
{
	t_args_dasm *argument;

	if (!(argument = malloc(sizeof(t_args_dasm))))
		return (NULL);
	argument->data = name;
	argument->size = 0;
	argument->next = NULL;
	return (argument);
}