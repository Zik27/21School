/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:09:32 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/04 18:38:48 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	free_map(char **map, int count)
{
	int		i;

	i = 0;
	while (i < count)
		free(map[i++]);
	free(map);
}

char	**build_map(int len_side)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(map = (char **)malloc(sizeof(*map) * len_side + 1)))
		return (NULL);
	while (i < len_side)
	{
		j = 0;
		if (!(map[i] = ft_strnew(len_side)))
		{
			free_map(map, i);
			return (NULL);
		}
		while (j < len_side)
			map[i][j++] = '.';
		i++;
	}
	map[i] = NULL;
	return (map);
}