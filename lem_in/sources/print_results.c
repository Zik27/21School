/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_results.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:25:16 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/11 17:27:06 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*make_step(t_path *path, int id)
{
	int	tmp;
	t_path	*end;

	end = NULL;
	if (path->room_path->ant_id == -1 && id != -1)
	{
		path->room_path->ant_id = id;
		if (!path->next)
			end = path;
	}
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

void	print_solution(t_path *path, char **result)
{
	char *tmp;
	char *free_str;

	while (path)
	{
		if (path->room_path->ant_id == -1)
		{
			path = path->next;
			continue ;
		}
		free_str = ft_itoa(path->room_path->ant_id);
		tmp = ft_strjoin("L", free_str);
		free(free_str);
		free_str = ft_strjoin(tmp, "-");
		free(tmp);
		tmp = free_str;
		free_str = ft_strjoin(tmp, path->room_path->name);
		free(tmp);
		tmp = free_str;
		free_str = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = *result;
		*result = ft_strjoin(free_str, tmp);
		if (ft_strcmp(tmp, ""))
			free(tmp);
		free(free_str);
		path = path->next;
	}
}

void	step_by_step(t_paths *paths, int count_ants, int count_lines)
{
	int		id;
	t_paths	*ways;
	t_path	*end;
	char	*result;

	ways = paths;
	id = 1;
	while (count_lines)
	{
		while (ways)
		{
			result = "";
			if (count_ants - id >= 0 && count_lines >= ways->size)
				end = make_step(ways->path->next, id++);
			else
				end = make_step(ways->path->next, -1);
			print_solution(ways->path, &result);
			if (end)
				end->room_path->ant_id = -1;
			ft_putstr(result);
			if (ft_strcmp(result, ""))
				free(result);
			ways = ways->next;
		}
		count_lines--;
		ways = paths;
		ft_putchar('\n');
		result = "";
	}
}

void	print_out(t_file_txt *input, t_paths *paths, int count_ants, int count_lines)
{
	while (input)
	{
		ft_putendl(input->text);
		input = input->next;
	}
	ft_putstr("\n");
	step_by_step(paths, count_ants, count_lines);
}
