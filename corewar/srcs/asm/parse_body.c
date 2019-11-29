/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:47:24 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 17:47:30 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_instruction(t_player *player, t_instr *instr)
{
	t_instr *tmp;

	tmp = player->instr;
	if (!tmp)
		player->instr = instr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = instr;
	}
}

void	upd_bit_info(t_player *player)
{
	player->last_instr->start_bit = player->current_bit;
	player->current_bit += player->last_instr->size_exec_code;
}

void	search_instruction(t_player *player, char *line)
{
	int		len_token;

	len_token = 0;
	del_comment(line);
	while (line[player->num_col])
	{
		if (is_comment(line[player->num_col]))
			return ;
		if (line[player->num_col] == SEPARATOR_CHAR)
			player->num_col++;
		else if (is_whitespace(line[player->num_col]))
			skip_tab_space(player, line, SKIP_QUOTE);
		else
		{
			len_token = search_length_token(player, line);
			if (is_label(line, player, len_token))
				handling_label(player, line, len_token - 1);
			else if (!(is_instruction(player, line)))
				error_file("Syntax error", player->num_row,
						player->num_col + 1);
		}
	}
	if (len_token > 0 && player->last_instr && !player->flag_lable_exist)
		upd_bit_info(player);
}

void	reading_body_champion(int fd, t_player *player)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		player->num_row++;
		search_instruction(player, line);
		player->num_col = 0;
		free(line);
	}
}
