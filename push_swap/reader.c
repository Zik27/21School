/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:37:13 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/26 18:06:58 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_lst	*get_next_min(t_lst *stack)
{
	t_lst	*min;
	t_lst	*tmp;
	int		flag;

	tmp = stack;
	flag = 0;
	while (tmp)
	{
		if (tmp->index == 0)
		{
			min = tmp;
			flag = 1;
		}
		tmp = tmp->next;
	}
	while (stack && flag)
	{
		if (stack->value < min->value && !stack->index)
			min = stack;
		stack = stack->next;
	}
	return (flag == 1 ? min : NULL);
}

void		indexing(t_head **head)
{
	t_lst	*current;
	int		index;

	index = 1;
	while ((current = get_next_min((*head)->a)))
		current->index = index++;
}


void	print_stacks(t_head **head)
{
	t_lst	*a;
	t_lst	*b;
	int		tmp;

	a = (*head)->a;
	b = (*head)->b;
	ft_printf(RED_DARK"\t\tSTACK A%60sSTACK B\n"RESET, " ");
	while (a || b)
	{
		if (a && !b)
		{
			ft_printf(GREEN"[%11d]  "RESET, a->value);
			tmp = a->index;
			while (a->index-- > 0)
				ft_printf("#");
			a->index = tmp;
			ft_printf("\n");
			a = a->next;
		}
		else if (!a && b)
		{
			ft_printf(GREEN"%64s[%11d] "RESET, " ", b->value);
			tmp = b->index;
			while (b->index-- > 0)
				ft_printf("#");
			b->index = tmp;
			ft_printf("\n");
			b = b->next;
		}
		else
		{
			ft_printf(GREEN"[%11d] "RESET, a->value);
			tmp = a->index;
			while (a->index-- > 0)
				ft_printf("#");
			a->index = tmp;
			ft_printf(GREEN"%*s[%11d] "RESET, 50 - tmp, " ", b->value);
			tmp = b->index;
			while (b->index-- > 0)
				ft_printf("#");
			b->index = tmp;
			ft_printf("\n");
			b = b->next;
			a = a->next;
		}
	}
}

int	read_command(t_head **head)
{
	char	*line;

	indexing(head);
	print_stacks(head);
	while (get_next_line(0, &line) == 1)
	{
		if (!ft_strcmp(line, "sa"))
			do_sa(head);
		else if (!ft_strcmp(line, "sb"))
			do_sb(head);
		else if (!ft_strcmp(line, "ss"))
			do_ss(head);
		else if (!ft_strcmp(line, "pa"))
			do_pa(head);
		else if (!ft_strcmp(line, "pb"))
			do_pb(head);
		else if (!ft_strcmp(line, "ra"))
			do_ra(head);
		else if (!ft_strcmp(line, "rb"))
			do_rb(head);
		else if (!ft_strcmp(line, "rr"))
			do_rr(head);
		else if (!ft_strcmp(line, "rra"))
			do_rra(head);
		else if (!ft_strcmp(line, "rrb"))
			do_rrb(head);
		else if (!ft_strcmp(line, "rrr"))
			do_rrr(head);
		else
		{
			free(line);
			return (0);
		}
		if ((*head)->do_debug)
			print_stacks(head);
		free(line);
	}
	return (1);
}
