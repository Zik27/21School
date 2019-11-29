/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:15:41 by aestella          #+#    #+#             */
/*   Updated: 2019/11/29 13:25:15 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_instr_name(char *line, int *i_names, t_player *pl)
{
	int		i;
	int		j;
	char	*instr_name;

	i = 0;
	while (i_names[i] != -1)
	{
		j = 0;
		instr_name = g_instr[i_names[i] - 1].name;
		while (instr_name[j] && !(is_whitespace(line[pl->num_col + j]))
				&& instr_name[j] == line[pl->num_col + j])
			j++;
		if (instr_name[j] == '\0' && check_next_sign(line[pl->num_col + j]))
		{
			instr_name = ft_strsub(line, pl->num_col, j);
			pl->num_col += j;
			check_instruction(pl, instr_name, &(line[pl->num_col]), i_names[i]);
			return (j);
		}
		i++;
	}
	return (0);
}

int		is_instruction(t_player *player, char *line)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i_name[i][0] != -1 &&
			line[player->num_col] != g_instr[i_name[i][0] - 1].name[0])
		i++;
	if (i >= 8)
		return (0);
	else
		return (check_instr_name(line, i_name[i], player));
}

void	ft_link_new_instr(t_instr *new_instr, t_player *player)
{
	if (player->instr == NULL)
	{
		player->instr = new_instr;
		player->last_instr = new_instr;
	}
	else
	{
		player->last_instr->next = new_instr;
		player->last_instr = player->last_instr->next;
	}
	if (player->flag_lable_exist)
	{
		link_lable_to_instr(new_instr, player->flag_lable_exist);
		player->flag_lable_exist = NULL;
	}
}

void	check_instruction(t_player *player, char *instr, char *line, int i)
{
	t_instr *new_instr;

	if (!(new_instr = init_instr(instr)) ||
			!(new_instr->args = (t_tokens**)malloc(sizeof(t_tokens*)
					* (g_instr[i - 1].args_num + 1))))
		error("Memory allocation error");
	ft_link_new_instr(new_instr, player);
	player->last_instr->code_op = g_instr[i - 1].code;
	player->last_instr->count_args = g_instr[i - 1].args_num;
	player->last_instr->args[g_instr[i - 1].args_num] = NULL;
	check_arguments(player, line);
}

void	change_col_num(t_player *player, char **arg_line, char *arg)
{
	int num;

	if (arg)
	{
		num = ft_strstr(*arg_line, arg) - *arg_line;
		player->num_col += num;
		*arg_line = *arg_line + num;
	}
}
