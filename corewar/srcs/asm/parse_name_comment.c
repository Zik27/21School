/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:14:23 by vurrigon          #+#    #+#             */
/*   Updated: 2019/11/05 12:32:06 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_space_after_name_comment(t_player *player, char *line, int len)
{
	if ((line[len + player->num_col] == '\t'
				|| line[len + player->num_col] == ' '
				|| line[len + player->num_col] == '"'))
		return (1);
	else
		return (0);
}

int		check_command(char *line, t_player *pl, int len_n, int len_c)
{
	if (!ft_strncmp(&(line[pl->num_col]), NAME_CMD_STRING, len_n)
			&& is_space_after_name_comment(pl, line, len_n))
	{
		if (pl->name)
			error_file("The name of the champion has already been determined",
					pl->num_row, pl->num_col + 1);
		pl->num_col += len_n;
		write_name(pl, line);
	}
	else if (!ft_strncmp(&(line[pl->num_col]), COMMENT_CMD_STRING, len_c)
			&& is_space_after_name_comment(pl, line, len_c))
	{
		if (pl->comment)
			error_file("The comment of the champion has already been "
					"determined", pl->num_row, pl->num_col + 1);
		pl->num_col += len_c;
		write_comment(pl, line);
	}
	else
		return (0);
	return (1);
}

void	check_comment(int fd, int lpos, char *buf)
{
	while (lpos-- > 0)
	{
		lseek(fd, lpos, SEEK_SET);
		read(fd, buf, 1);
		if (*buf == COMMENT_CHAR || *buf == ALT_COMMENT_CHAR)
		{
			lseek(fd, --lpos, SEEK_SET);
			read(fd, buf, 1);
			if (*buf == '\n')
				return ;
			else
				error("Syntax error - no newline at the end");
		}
		if (*buf == '\n')
			error("Syntax error - no newline at the end");
	}
}

void	search_continue(t_player *player, char *line)
{
	char	*quote;
	char	*tmp;

	tmp = NULL;
	quote = ft_strchr(line, '"');
	if (!player->is_finished_com && !quote)
		continue_name_com(NAME, player, line, &tmp);
	else if (!player->is_finished_name && !quote)
		continue_name_com(COMMENT, player, line, &tmp);
	else if (!player->is_finished_com)
		tmp = finish_add_nam_com(COMMENT, player, line, quote);
	else if (!player->is_finished_name)
		tmp = finish_add_nam_com(NAME, player, line, quote);
	if (quote)
	{
		player->num_col += quote - line;
		check_after_quote(player, quote);
	}
	if (tmp)
		free(tmp);
}

void	search_comment_name(t_player *player, char *line)
{
	while (line[player->num_col])
	{
		if (is_whitespace(*line))
			skip_tab_space(player, line, SKIP_QUOTE);
		if (is_comment(line[player->num_col]))
			return ;
		else if (line[player->num_col] == '.')
		{
			if (!check_command(line, player, ft_strlen(NAME_CMD_STRING),
						ft_strlen(COMMENT_CMD_STRING)))
				error_file("Unknown command", player->num_row,
						player->num_col + 1);
			return ;
		}
		else if (line[player->num_col] != ' ' && line[player->num_col] != '\t')
			error_file("Syntax error", player->num_row, player->num_col + 1);
		player->num_col++;
	}
}
