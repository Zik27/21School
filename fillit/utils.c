/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:41:52 by djast             #+#    #+#             */
/*   Updated: 2019/01/06 11:43:17 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		get_right_width(int *data)
{
	int zero;
	int one;
	int two;
	int i;

	zero = 0;
	one = 0;
	two = 0;
	i = 0;
	while (i++ < 3)
	{
		if (data[i - 1] >= 1 && data[i - 1] <= 3)
			zero++;
		else if (data[i - 1] >= 11 && data[i - 1] <= 12)
			one++;
		else if (data[i - 1] == 21)
			two++;
	}
	if (zero >= one && zero >= two)
		return (zero);
	else if (one >= zero && one >= two)
		return (one);
	else
		return (two);
}

int		get_left_width(int *data)
{
	int one;
	int two;
	int i;

	one = 0;
	two = 0;
	i = 0;
	while (i++ < 3)
	{
		if (data[i - 1] >= 8 && data[i - 1] <= 9)
			one++;
		else if (data[i - 1] == 19)
			two++;
	}
	return (one >= two ? one : two);
}

int		get_height(int *data)
{
	if (data[0] == 30 || data[1] == 30 || data[2] == 30)
		return (4);
	else if ((data[0] >= 19 && data[0] <= 21) ||
		(data[1] >= 19 && data[1] <= 21) || (data[2] >= 19 && data[2] <= 21))
		return (3);
	else if ((data[0] >= 8 && data[0] <= 12) ||
		(data[1] >= 8 && data[1] <= 12) || (data[2] >= 8 && data[2] <= 12))
		return (2);
	else
		return (1);
}

int		print_map(char **map, int size)
{
	int i;

	i = 0;
	while (i++ < size)
		ft_putendl(map[i - 1]);
	return (0);
}
