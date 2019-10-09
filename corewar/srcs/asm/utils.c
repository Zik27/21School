/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:40:19 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/09 13:06:20 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_strndup(const char *src, int i)
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

int	is_comment(char *line, t_player *player)
{
	if (line[player->num_col] == ALT_COMMENT_CHAR ||
			line[player->num_col] == COMMENT_CHAR)
		return (1);
	return (0);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
