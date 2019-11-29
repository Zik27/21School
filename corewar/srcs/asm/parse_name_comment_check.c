/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:21:49 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 18:21:52 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	write_name(t_player *player, char *line)
{
	char	*tmp;
	int		length;
	char	*tmp_free;

	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) != QUOTE)
		error_file("Syntax error", player->num_row, player->num_col + 1);
	player->num_col++;
	tmp = ft_strchr(&line[player->num_col], '"');
	if (!tmp)
	{
		player->is_finished_name = 0;
		tmp_free = ft_strdup(&line[player->num_col]);
		player->name = ft_strjoin(tmp_free, "\n");
		free(tmp_free);
		return ;
	}
	else if (player->name != NULL)
		error_file("Syntax error", player->num_row, player->num_col + 1);
	length = tmp - &line[player->num_col];
	check_len_name_comment(NAME, length);
	tmp = &line[player->num_col];
	player->num_col += length + 1;
	check_end_comment(player, line);
	player->name = ft_strndup(tmp, length);
	line += player->num_col;
}

void	write_comment(t_player *player, char *line)
{
	char	*tmp;
	int		length;
	char	*tmp_free;

	if (skip_tab_space(player, line, STOP_BEFORE_QUOTE) != QUOTE)
		error_file("Syntax error", player->num_row, player->num_col + 1);
	player->num_col++;
	tmp = ft_strchr(&line[player->num_col], '"');
	if (!tmp)
	{
		player->is_finished_com = 0;
		tmp_free = ft_strdup(&line[player->num_col]);
		player->comment = ft_strjoin(tmp_free, "\n");
		free(tmp_free);
		return ;
	}
	else if (player->comment != NULL)
		error_file("Syntax error", player->num_row, player->num_col + 1);
	length = tmp - &line[player->num_col];
	check_len_name_comment(COMMENT, length);
	tmp = &line[player->num_col];
	player->num_col += length + 1;
	check_end_comment(player, line);
	player->comment = ft_strndup(tmp, length);
	line += player->num_col;
}

void	continue_name_com(int flag, t_player *player, char *line, char **tmp)
{
	if (flag == NAME)
	{
		*tmp = ft_strjoin(player->comment, line);
		if (player->comment)
			free(player->comment);
		player->comment = ft_strjoin(*tmp, "\n");
	}
	else if (flag == COMMENT)
	{
		*tmp = ft_strjoin(player->name, line);
		if (player->name)
			free(player->name);
		player->name = ft_strjoin(*tmp, "\n");
	}
}

char	*finish_add_nam_com(int flag, t_player *player, char *line, char *quote)
{
	char	*tmp_end;
	char	*tmp;

	tmp = NULL;
	if (flag == COMMENT)
	{
		tmp = ft_strsub(line, 0, quote - line);
		tmp_end = ft_strjoin(player->comment, tmp);
		free(player->comment);
		player->comment = tmp_end;
		player->is_finished_com = 1;
	}
	else if (flag == NAME)
	{
		tmp = ft_strsub(line, 0, quote - line);
		tmp_end = ft_strjoin(player->name, tmp);
		free(player->name);
		player->name = tmp_end;
		player->is_finished_name = 1;
	}
	return (tmp);
}
