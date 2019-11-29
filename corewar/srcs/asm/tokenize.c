/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:16:41 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/22 18:31:44 by aestella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		search_length_token(t_player *player, char *line)
{
	int	i;
	int	len;

	i = player->num_col;
	len = 0;
	while (line[i] && line[i] != SEPARATOR_CHAR && !is_whitespace(line[i]) &&
			!is_comment(line[i]))
	{
		if ((line[i] == LABEL_CHAR && line[i - 1] != DIRECT_CHAR))
		{
			len++;
			break ;
		}
		else if (line[i] == DIRECT_CHAR && len)
			break ;
		i++;
		len++;
	}
	return (len);
}

t_type	know_type(char *token)
{
	if (token[0] == 'r')
		return (REGISTER);
	else if (token[0] == DIRECT_CHAR && token[1] == LABEL_CHAR)
		return (DIRECT_LABEL);
	else if (token[0] == DIRECT_CHAR)
		return (DIRECT);
	else if (token[0] == LABEL_CHAR)
		return (INDIRECT_LABEL);
	else if (ft_isdigit(token[0]) || (token[0] == '-' && ft_isdigit(token[1])))
		return (INDIRECT);
	else
		return (0);
}
