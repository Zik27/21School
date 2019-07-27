/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:16:23 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:19:48 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		get_total_steps(int step_a, int step_b)
{
	int	sum_step;

	sum_step = 0;
	if ((step_a <= 0 && step_b >= 0) || (step_a >= 0 && step_b <= 0))
		sum_step = step_b - step_a;
	else if (step_a < 0 && step_b < 0)
	{
		if (step_a < step_b)
			sum_step = -step_a;
		else
			sum_step = -step_b;
	}
	else if (step_a > 0 && step_b > 0)
	{
		if (step_a > step_b)
			sum_step = step_a;
		else
			sum_step = step_b;
	}
	return (sum_step < 0 ? -sum_step : sum_step);
}

int		get_count_smallest(int length, t_lst *stack)
{
	int		min;
	int		count;

	min = get_smallest(stack);
	count = 0;
	while (stack)
	{
		if (stack->value == min)
			return (count > length - count ? -(length - count) : count);
		count++;
		stack = stack->next;
	}
	return (0);
}

int		check_stack_a(int value_b, t_head *head)
{
	t_lst	*a;
	t_lst	*a_next;
	int		len_a;
	int		count;

	a = head->a;
	a_next = a->next;
	len_a = get_len_stack(a);
	count = 1;
	if (value_b < get_smallest(a))
		return (get_count_smallest(len_a, a));
	while (a_next)
	{
		if (a->value < value_b && a_next->value > value_b)
			return (count > len_a - count ? -(len_a - count) : count);
		a = a_next;
		a_next = a->next;
		count++;
	}
	return (0);
}

int		check_stack_b(int value, t_head *head)
{
	int		steps;
	int		len_b;
	t_lst	*b;

	steps = 0;
	len_b = get_len_stack(head->b);
	b = head->b;
	while (value != b->value)
	{
		steps++;
		b = b->next;
	}
	steps = steps > len_b - steps ? -(len_b - steps) : steps;
	return (steps);
}
