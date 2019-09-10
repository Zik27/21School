/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_results.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:25:16 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/08 15:20:45 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*make_step(t_path *path, int id)
{
	int	tmp;
	t_path	*end;

	end = NULL;
	if (path->room_path->ant_id == -1 && id != -1)
		path->room_path->ant_id = id;
	else
	{
		tmp = path->room_path->ant_id;
		path->room_path->ant_id = id;
		path = path->next;
		while (path)
		{
			ft_swap(&tmp, &path->room_path->ant_id);
			if (id > 0 && tmp == -1)
				break ;
			if (!path->next)
				end = path;
			path = path->next;
		}
	}
	return (end);
}

void	print_way(t_path *way)
{
	//printf("WAY == %p\n", way);
	while (way)
	{
		printf("ID == %d\n", way->room_path->ant_id);
		way = way->next;
	}
	printf("################\n");
}

void	print_solution(t_path *path, t_paths *paths)
{
	while (path)
	{
		if (path->room_path->ant_id == -1)
		{
			path = path->next;
			continue ;
		}
		ft_putchar('L');
		ft_putnbr(path->room_path->ant_id);
		ft_putchar('-');
		ft_putstr(path->room_path->name);
		if (paths->next || path->next)
			ft_putchar(' ');
		path = path->next;
	}
}

void	step_by_step(t_paths *paths, int count_ants, int count_lines)
{
	int		id;
	t_paths	*ways;
	t_path	*end;

	ways = paths;
	id = 1;
	printf("COUINT LINES == %d\n", count_lines);
	printf("COUNT ANTS == %d\n", count_ants);
	while (count_lines)
	{
		while (ways)
		{
			//printf("count_lines ==  %d, size == %d\n", count_lines, ways->size);
			if (count_ants - id >= 0 && count_lines >= ways->size)
				end = make_step(ways->path->next, id++);
			else
				end = make_step(ways->path->next, -1);
			print_solution(ways->path, ways);
			if (end)
				end->room_path->ant_id = -1;
			ways = ways->next;
		}
		//printf("EXIT\n");
		count_lines--;
		ways = paths;
		ft_putchar('\n');
	}
}

void	print_out(t_file_txt *input, t_paths *paths, int count_ants, int count_lines)
{
	input++;
	// while (input)
	// {
	// 	ft_putendl(input->text);
	// 	input = input->next;
	// }
	// ft_putstr("\n");
	step_by_step(paths, count_ants, count_lines);
}
