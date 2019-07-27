/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:37:13 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:50:41 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		commands_3(t_head **head, char **line)
{
	if (!ft_strcmp(*line, "rra"))
	{
		do_rra(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "rrb"))
	{
		do_rrb(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "rrr"))
	{
		do_rrr(head);
		return (1);
	}
	return (0);
}

int		commands_2(t_head **head, char **line)
{
	if (!ft_strcmp(*line, "pb"))
	{
		do_pb(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "ra"))
	{
		do_ra(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "rb"))
	{
		do_rb(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "rr"))
	{
		do_rr(head);
		return (1);
	}
	return (commands_3(head, line));
}

int		commands(t_head **head, char **line)
{
	if (!ft_strcmp(*line, "sa"))
	{
		do_sa(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "sb"))
	{
		do_sb(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "ss"))
	{
		do_ss(head);
		return (1);
	}
	else if (!ft_strcmp(*line, "pa"))
	{
		do_pa(head);
		return (1);
	}
	return (commands_2(head, line));
}

int		read_command(t_head **head)
{
	char	*line;

	indexing(head);
	if ((*head)->do_debug)
		print_stacks(*head, NULL, 1);
	while (get_next_line(0, &line) == 1)
	{
		if (!commands(head, &line))
		{
			free(line);
			return (0);
		}
		if ((*head)->do_debug)
			print_stacks(*head, line, 1);
		free(line);
	}
	return (1);
}
