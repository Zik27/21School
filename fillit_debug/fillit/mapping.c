/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:09:32 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/05 20:10:38 by djast            ###   ########.fr       */
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
	if (!(map = (char **)malloc(sizeof(char *) * (len_side + 1))))
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

void	clear_map(char **map, int *data, int error_index, int *coords)
{
	int cube_now;

	map[coords[0]][coords[1]] = '.';
	while (error_index-- != 0)
	{
		cube_now = data[error_index];
		if (cube_now >= 1 && cube_now <= 3)
			map[coords[0]][coords[1] + cube_now] = '.';
		else if (cube_now >= 8 && cube_now <= 12)
			map[coords[0] + 1][coords[1] + cube_now - 10] = '.';
		else if (cube_now >= 19 && cube_now <= 21)
			map[coords[0] + 2][coords[1] + cube_now - 20] = '.';
		else if (cube_now == 30)
			map[coords[0] + 3][coords[1]] = '.';
	}
}

int		change_point(int cube_now, char **map, int coords[2], char symbol)
{
	if (cube_now >= 1 && cube_now <= 3 &&
		map[coords[0]][coords[1] + cube_now] == '.')
		map[coords[0]][coords[1] + cube_now] = symbol;
	else if (cube_now >= 8 && cube_now <= 12 &&
		map[coords[0] + 1][coords[1] + cube_now - 10] == '.')
		map[coords[0] + 1][coords[1] + cube_now - 10] = symbol;
	else if (cube_now >= 19 && cube_now <= 21 &&
		map[coords[0] + 2][coords[1] + cube_now - 20] == '.')
		map[coords[0] + 2][coords[1] + cube_now - 20] = symbol;
	else if (cube_now == 30 && map[coords[0] + 3][coords[1]] == '.')
		map[coords[0] + 3][coords[1]] = symbol;
	else
		return (0);
	return (1);
}

int		place(int *data, char **map, int x, int y)
{
	static char	symbol = 'A';
	int			cube_now;
	int			i;
	int			coords[2];

	if (data == NULL)
		return (symbol--);
	i = 1;
	if (map[y][x] != '.')
		return (0);
	map[y][x] = symbol;
	while (i != 4)
	{
		cube_now = data[i - 1];
		coords[0] = y;
		coords[1] = x;
		if (!(change_point(cube_now, map, coords, symbol)))
		{
			clear_map(map, data, i - 1, coords);
			return (0);
		}
		i++;
	}
	symbol++;
	return (1);
}
