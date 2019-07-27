/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:49:36 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:20:36 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_lst	*choose_min_step(t_lst *stack)
{
	t_lst	*min_step;

	min_step = stack;
	stack = stack->next;
	while (stack)
	{
		if (stack->sum_step < min_step->sum_step)
			min_step = stack;
		stack = stack->next;
	}
	return (min_step);
}

void	check_count_op(t_head **head)
{
	t_lst	*b;
	int		count_b;
	int		count_a;

	b = (*head)->b;
	while (b)
	{
		count_b = check_stack_b(b->value, *head);
		b->count_op_b = count_b;
		count_a = check_stack_a(b->value, *head);
		b->count_op_a = count_a;
		b->sum_step = get_total_steps(count_a, count_b);
		b = b->next;
	}
}

void	main_sorting(t_head **head)
{
	t_lst *choosen;

	while ((*head)->b)
	{
		check_count_op(head);
		choosen = choose_min_step((*head)->b);
		solver(head, choosen);
	}
	align_stack(head);
}
