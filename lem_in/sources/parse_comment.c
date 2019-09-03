/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:46:52 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/03 11:14:52 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parse_comment(char *str, t_map *map)
{
	if (*str == '#' && *(str + 1) == '#')
	{
		if (ft_strcmp(str, "##start") == 0 && !map->prev_command)
			map->prev_command = START;
		else if (ft_strcmp(str, "##end") == 0 && !map->prev_command)
			map->prev_command = EXIT;
	}
}
