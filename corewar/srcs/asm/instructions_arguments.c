/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_arguments.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:48:10 by aestella          #+#    #+#             */
/*   Updated: 2019/11/29 13:23:51 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern	t_func_pointer g_funk_array[5];

void	check_param_count(int i, int separ, t_instr *instr, t_player *player)
{
	if (i - separ >= g_instr[instr->code_op - 1].args_num)
		error_name("Invalid parameter count for instruction", instr->instr,
				player->num_row, player->num_col);
}

void	check_end_param_count(int i, int separ, t_instr *instr, t_player *pl)
{
	if (i - separ != g_instr[instr->code_op - 1].args_num)
		error_name("Invalid parameter count for instruction", instr->instr,
				pl->num_row, pl->num_col);
}

void	check_arg_exist(char *arg, t_player *pl)
{
	if (arg == NULL)
		error_file("Syntax error", pl->num_row, pl->num_col + 1);
}

void	check_arg_num(char **args, t_instr *instr, t_player *pl, char *arg_line)
{
	int		i;
	int		sep;
	t_type	type;

	i = -1;
	sep = 0;
	while (args[++i])
	{
		change_col_num(pl, &arg_line, args[i]);
		if (i % 2 == 1)
		{
			check_separator_char(&sep, &i, args[i], instr->args[sep]);
			change_col_num(pl, &arg_line, args[i]);
		}
		check_param_count(i, sep, instr, pl);
		check_arg_exist(args[i], pl);
		if (!(type = know_type(args[i])))
			error_type(instr->instr, type, sep + 1);
		check_type_arg(type, g_instr[instr->code_op - 1].args_types[sep],
				instr, sep);
		g_funk_array[type - 1](instr->args[sep], args[i], instr->code_op, pl);
	}
	if (i > 0 && args[i - 1])
		pl->num_col += ft_strlen(args[i - 1]);
	check_end_param_count(i, sep, instr, pl);
}

int		check_arguments(t_player *player, char *arg_line)
{
	char	**args;

	del_comment(arg_line);
	args = ft_split_argument(arg_line);
	if (args == NULL)
		error_name("No arguments for instruction", player->last_instr->instr,
				player->num_row, player->num_col);
	else
	{
		check_arg_num(args, player->last_instr, player, arg_line);
		player->last_instr->size_exec_code = calculate_size(player->last_instr);
	}
	free(args);
	return (0);
}
