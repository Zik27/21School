/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:57:54 by djast             #+#    #+#             */
/*   Updated: 2019/09/10 11:14:29 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		compare_steps(int ants, int steps, int count_paths,
												int *least_steps)
{
	int	tmp;

	if ((steps + ants - count_paths) % count_paths == 0)
		tmp = (steps + ants - count_paths) / count_paths;
	else
		tmp = ((steps + ants - count_paths) / count_paths) + 1;
	//printf("sum: %d, count: %d\n", tmp, count_paths);
	if (tmp <= *least_steps)
	{
		*least_steps = tmp;
		return (1);
	}
	return (0);

}

static int		get_steps(t_paths *paths, int count_paths)
{
	int	size;

	size = 0;
	while (count_paths--)
	{
		if (!paths)
			return (0);
		else
			size += paths->size;
		paths = paths->next;
	}
	return (size);
}

static int		get_path_last_size(t_paths *paths, int count_paths)
{
	while (count_paths--)
		paths = paths->next;
	return (paths->size);
}

int		choose_path(int ants, t_paths *paths, t_map *map)
{
	int	count_paths;
	int	steps;
	int min_steps;

	count_paths = 1;
	min_steps = INT_MAX;
	while ((steps = get_steps(paths, count_paths)) != 0)
	{
		if (compare_steps(ants, steps, count_paths, &min_steps) == 0 ||
		get_path_last_size(paths, count_paths - 1) > min_steps)
			break ;
		count_paths++;
	}
	map->count_out_line = min_steps;
	return (count_paths - 1);
}