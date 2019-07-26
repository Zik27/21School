/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:45:28 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/26 16:50:53 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	check_sort(t_head *head)
{
	t_lst	*b;
	t_lst	*a;
	int		value;

	a = head->a;
	b = head->b;
	if (!a || b)
		return (0);
	value = a->value;
	while (a->next)
	{
		a = a->next;
		if (value > a->value)
			return (0);
		value = a->value;
	}
	return (1);
}

int	get_len_stack(t_lst *stack)
{
	int	length;

	length = 0;
	while (stack)
	{
		length++;
		stack = stack->next;
	}
	return (length);
}

int get_smallest(t_lst *stack)
{
	int	smallest;

	smallest = stack->value;
	while (stack->next)
	{
		stack = stack->next;
		smallest = smallest > stack->value ? stack->value : smallest; 
	}
	return (smallest);
}

int get_max(t_lst *stack)
{
	int	max;

	max = stack->value;
	while (stack->next)
	{
		stack = stack->next;
		max = max < stack->value ? stack->value : max; 
	}
	return (max);
}

void	swap_value(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}