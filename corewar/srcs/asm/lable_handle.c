/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:01:25 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 22:01:33 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_label(t_player *player, char *label)
{
	int		i;
	t_label	*new_label;

	i = 0;
	while (label[i])
		if (!ft_strchr(LABEL_CHARS, label[i++]))
			error_file("Invalid label name", player->num_row,
					player->num_col + 1);
	if (!(new_label = init_label(label)))
		error("Memory allocation error");
	if (player->labels == NULL)
	{
		player->labels = new_label;
		player->last_label = new_label;
	}
	else
	{
		player->last_label->next = new_label;
		new_label->prev = player->last_label;
		player->last_label = player->last_label->next;
	}
}

int		handling_label(t_player *player, char *line, int len)
{
	check_label(player, ft_strsub(line, player->num_col, len));
	player->flag_lable_exist = player->last_label;
	player->num_col += len + 1;
	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
		{
			printf("Nothing after label\n");
			break ;
		}
		else if (is_whitespace(line[player->num_col]))
		{
			skip_tab_space(player, line, SKIP_QUOTE);
		}
		else if (!(is_instruction(player, line)))
		{
			error_file("Syntax error", player->num_row, player->num_col + 1);
			break ;
		}
	}
	return (0);
}

void	link_lable_to_instr(t_instr *instr, t_label *label)
{
	t_label *tmp;

	label->instr = instr;
	instr->label = label;
	tmp = label;
	while (tmp->prev && tmp->prev->instr == NULL)
	{
		tmp = tmp->prev;
		tmp->instr = instr;
	}
}
