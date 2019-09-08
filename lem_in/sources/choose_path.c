/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:57:54 by djast             #+#    #+#             */
/*   Updated: 2019/09/07 19:58:45 by djast            ###   ########.fr       */
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
		tmp = (steps + ants - count_paths) / count_paths + 1;
	if (tmp < *least_steps)
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

int		choose_path(int ants, t_paths *paths)
{
	int	count_paths;
	int	steps;
	int min_steps;

	count_paths = 1;
	min_steps = INT_MAX;
	while ((steps = get_steps(paths, count_paths)) != 0)
	{
		if (compare_steps(ants, steps, count_paths, &min_steps) == 0)
			break;
		count_paths++;
	}
	return (count_paths - 1);
}