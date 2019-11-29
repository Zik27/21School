/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment_check_error.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:24:59 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 18:25:27 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_len_name_comment(int flag, int len)
{
	if (flag == NAME)
	{
		if (len > PROG_NAME_LENGTH)
			error("Champion name too long (Max length 128)");
	}
	else if (flag == COMMENT)
	{
		if (len > COMMENT_LENGTH)
			error("Champion comment too long (Max length 2048)");
	}
}

void	check_end_comment(t_player *player, char *line)
{
	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) &&
	!is_comment(line[player->num_col]))
		error_file("Syntax error", player->num_row, player->num_col + 1);
}

void	check_after_quote(t_player *player, char *line)
{
	int i;

	i = 1;
	while (line[i])
	{
		if (is_whitespace(line[i]))
		{
			i++;
			continue;
		}
		if (is_comment(line[i]))
			break ;
		if (line[i] != '\0')
			error_file("Syntax error",
					player->num_row, player->num_col + i + 1);
		i++;
	}
}

void	check_len_name_com(t_player *player)
{
	if (ft_strlen(player->name) > PROG_NAME_LENGTH)
		error("Champion name too long (Max length 128)");
	else if (ft_strlen(player->comment) > COMMENT_LENGTH)
		error("Champion comment too long (Max length 2048)");
}

int		check_name_comment(int fd, t_player *player)
{
	char *line;

	while (get_next_line(fd, &line) == 1)
	{
		player->num_row++;
		if (!player->is_finished_name || !player->is_finished_com)
			search_continue(player, line);
		else
		{
			search_comment_name(player, line);
			if (player->comment && player->name && player->is_finished_com &&
				player->is_finished_name)
			{
				player->num_col = 0;
				check_len_name_com(player);
				free(line);
				return (1);
			}
		}
		player->num_col = 0;
		free(line);
	}
	return (0);
}
