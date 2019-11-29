/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:53:24 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/22 17:34:09 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	error_file(char *str, int row, int col)
{
	row = row == 0 ? row + 1 : row;
	col = col == 0 ? col + 1 : col;
	ft_printf("[%d:%d] %s\n", row, col, str);
	exit(1);
}

void	error_name(char *str, char *name, int row, int col)
{
	row = row == 0 ? row + 1 : row;
	col = col == 0 ? col + 1 : col;
	ft_printf("[%d:%d] %s %s\n", row, col, str, name);
	exit(1);
}

void	error_type(char *instr, t_type type, int arg)
{
	if (type == INDIRECT || type == INDIRECT_LABEL)
		ft_printf("Invalid parameter number %d type "
				"indirect for instruction %s \n", arg, instr);
	else if (type == DIRECT || type == DIRECT_LABEL)
		ft_printf("Invalid parameter number %d type "
				"direct for instruction %s \n", arg, instr);
	else if (type == REGISTER)
		ft_printf("Invalid parameter number %d "
				"type register for instruction %s \n", arg, instr);
	else
		ft_printf("Invalid parameter number %d "
				"for instruction %s \n", arg, instr);
	exit(1);
}

void	error_arg(t_instr *inst, t_type type, int arg)
{
	t_tokens *a;

	if (arg)
		arg--;
	if (inst->args != NULL)
	{
		a = inst->args[arg];
		if (type == INDIRECT || type == INDIRECT_LABEL)
			ft_printf("[%d:%d] Invalid parameter number %d type indirect for"
					" instruction %s \n", a->row, a->col + 1, arg, inst->instr);
		else if (type == DIRECT || type == DIRECT_LABEL)
			ft_printf("[%d:%d] Invalid parameter number %d type direct for "
					"instruction %s \n", a->row, a->col + 1, arg, inst->instr);
		else if (type == REGISTER)
			ft_printf("[%d:%d] Invalid parameter number %d type register for "
					"instruction %s \n", a->row, a->col + 1, arg, inst->instr);
		else
			ft_printf("[%d:%d] Invalid parameter number %d for "
					"instruction %s \n", a->row, a->col + 1, arg, inst->instr);
		exit(1);
	}
	error_type(inst->instr, type, arg);
}
