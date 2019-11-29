/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:11:00 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 19:11:08 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_type_arg(t_type type, int need_type, t_instr *instr, int num)
{
	if (type == DIRECT_LABEL || type == INDIRECT_LABEL)
	{
		if (((type - 1) & need_type) != (type - 1))
			error_type(instr->instr, type, num);
	}
	else if ((type & need_type) != type)
		error_type(instr->instr, type, num);
	if (!(instr->args[num] = init_tokens(type)))
		exit(1);
}

int		arg_to_int(t_tokens *arg, t_instr *instr, int arg_num)
{
	char	*str;
	int		i;

	i = 0;
	str = arg->data;
	if (arg->type != INDIRECT)
		i++;
	if (str[i] == '-')
		i++;
	else if (str[i] == '\0')
		error_arg(instr, instr->args[arg_num]->type, arg_num + 1);
	while (str[i])
		if (!(isdigit(str[i++])))
			error_arg(instr, instr->args[arg_num]->type, arg_num + 1);
	if (arg->type != INDIRECT)
		return (ft_atoi(&(str[1])));
	return (ft_atoi(str));
}

void	lable_to_int(t_label *lables, t_instr *instr, int arg_num, t_player *pl)
{
	t_label	*tmp;
	char	*str_label;
	int		i;
	int		*data_int;

	tmp = lables;
	data_int = &(instr->args[arg_num]->data_int);
	while (tmp)
	{
		i = 1;
		str_label = instr->args[arg_num]->data;
		if (instr->args[arg_num]->type == DIRECT_LABEL)
			i++;
		if (!(ft_strcmp(&(str_label[i]), tmp->l_name)))
		{
			if (!tmp->instr)
				*data_int = pl->sum_size_exec_code - instr->start_bit;
			else
				*data_int = tmp->instr->start_bit - instr->start_bit;
		}
		tmp = tmp->next;
	}
	if (*data_int == -1)
		error_name("Lable", "not exist", instr->args[arg_num]->row,
				instr->args[arg_num]->col);
}

void	check_arg_is_digit(t_player *player)
{
	t_instr *instr;
	int		i;
	int		*data_int;

	if (!(instr = player->instr))
		error_file("Syntax error", player->num_row, player->num_col + 1);
	while (instr)
	{
		i = -1;
		while (++i < instr->count_args)
		{
			data_int = &(instr->args[i]->data_int);
			if (instr->args[i]->type == DIRECT_LABEL
					|| instr->args[i]->type == INDIRECT_LABEL)
				lable_to_int(player->labels, instr, i, player);
			else
			{
				*data_int = arg_to_int(instr->args[i], instr, i);
				if (instr->args[i]->type == REGISTER
						&& (*data_int < 1 || *data_int > 99))
					error_arg(instr, instr->args[i]->type, i + 1);
			}
		}
		instr = instr->next;
	}
}
