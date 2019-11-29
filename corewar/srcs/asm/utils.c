/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:40:19 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/22 22:01:08 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_strndup(const char *src, int i)
{
	int		a;
	char	*result_string;

	a = 0;
	if (!(result_string = ft_strnew(i)))
		return (NULL);
	while (src[a] && a < i)
	{
		result_string[a] = src[a];
		a++;
	}
	return (result_string);
}

int		is_comment(int chr)
{
	return (chr == ALT_COMMENT_CHAR || chr == COMMENT_CHAR);
}

int		skip_tab_space(t_player *player, char *line, int flag)
{
	while (line[player->num_col])
	{
		if (line[player->num_col] == ' ' || line[player->num_col] == '\t')
			player->num_col++;
		else if (line[player->num_col] == '"' && flag)
			return (QUOTE);
		else
			return (-1);
	}
	return (0);
}

void	del_comment(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != COMMENT_CHAR && line[i]
			&& line[i] != ALT_COMMENT_CHAR)
		i++;
	line[i] = '\0';
}

/*
 ** Есть в DASM
 */

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
