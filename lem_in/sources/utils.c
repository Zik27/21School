/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:02:42 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/10 11:16:58 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_file_txt(t_file_txt **input, char *line)
{
	t_file_txt	*tmp;

	if (!(*input)->next && !(*input)->text)
		(*input)->text = line;
	else
	{
		tmp = init_input_file(line);
		tmp->next = (*input);
		(*input) = tmp;
	}
}

void	reverse_input_file(t_file_txt **lst)
{
	t_file_txt	*current;
	t_file_txt	*before;
	t_file_txt	*after;

	current = *lst;
	after = 0;
	before = NULL;
	while (current)
	{
		after = current->next;
		current->next = before;
		before = current;
		current = after;
	}
	*lst = before;
}

void	reverse_paths(t_paths **paths)
{
	t_paths	*current;
	t_paths	*before;
	t_paths	*after;

	current = *paths;
	after = 0;
	before = NULL;
	while (current)
	{
		after = current->next;
		current->next = before;
		before = current;
		current = after;
	}
	*paths = before;
}

void	path_removal(t_paths *paths, int count_paths)
{
	t_paths		*tmp;
	while (paths)
	{
		if (!count_paths)
		{
			tmp->next = NULL;
			free_paths(paths);
			break ;
		}
		count_paths--;
		tmp = paths;
		paths = paths->next;
	}
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
