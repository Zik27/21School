/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:00:32 by aestella          #+#    #+#             */
/*   Updated: 2019/10/22 22:02:30 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	is_whitespace(int c)
{
	return (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

int	is_label(char *line, t_player *player, int len)
{
	len--;
	if (line[player->num_col + len] == LABEL_CHAR)
		return (1);
	return (0);
}

int	check_next_sign(char sign)
{
	return (is_whitespace(sign) || sign == '%' || sign == '-');
}

int	check_separator_char(int *sep, int *i, char *c, t_tokens *arg)
{
	if (*c != SEPARATOR_CHAR)
		error_file("Syntax error", arg->row,
				arg->col + ft_strlen(arg->data) + 1);
	else
	{
		free(c);
		(*sep)++;
		(*i)++;
	}
	return (1);
}
