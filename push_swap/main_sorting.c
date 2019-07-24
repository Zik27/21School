/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:49:36 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/24 17:07:11 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	align_stack(t_head **head)
{
	t_lst		*a;
	int			min;
	int			count;
	int			len;

	a = (*head)->a;
	min = get_smallest(a);
	len = get_len_stack(a);
	count = 0;
	if (min == a->value)
		return ;
	while (min != a->value)
	{
		count++;
		a = a->next;
	}
	if (len - count < count)
		while (len - count++ > 0)
			do_rra(head);
	else
		while (count-- > 0)
			do_ra(head);
}

int		get_total_steps(int step_a, int step_b)
{
	int	sum_step;

	if (step_a < 0 && step_b > 0)
		sum_step = step_b - step_a;
	else if (step_a > 0 && step_b < 0)
		sum_step = step_a - step_b;
	else
		sum_step = step_a + step_b;
	sum_step = sum_step < 0 ? -sum_step : sum_step;
	return (sum_step);
}

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

void check_count_op(t_head **head)
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
		//printf("COUNT_A === %d, COUNT_B === %d\n", count_a, count_b);
		b->sum_step = get_total_steps(count_a, count_b);
		//printf("RESULT === %d\n", b->sum_step);
		b = b->next;
	}
	//printf("AAAAAAA %d\n", all_sum);
}

void	main_sorting(t_head **head)
{
	t_lst *choosen;

	while ((*head)->b)
	{
		check_count_op(head);
		choosen = choose_min_step((*head)->b);





		//t_lst	*current;
		// if (!(*head)->b)
		// 	printf("B is NULL\n");
		// else
		// {
		// 	current = (*head)->b;
		// 	printf("B is not NULL\n");
		// 	while (current->next)
		// 	{
		// 		printf("nbr = %d\n", current->value);
		// 		current = current->next;
		// 	}
		// 	printf("nbr = %d\n", current->value);
		// }
		// if ((*head)->a)
		// {
		// 	t_lst	*current;
		// 	current = (*head)->a;
		// 	printf("A is not NULL\n");
		// 	while (current->next)
		// 	{
		// 		printf("nbr = %d\n", current->value);
		// 		current = current->next;
		// 	}
		// 	printf("nbr = %d\n", current->value);
		// }
		// else
		// 	printf("A is NULL\n");



		//printf("$$$$$$SOLVER$$$$$$$$\n");
		solver(head, choosen);
		// if (!(*head)->b)
		// 	printf("B is NULL\n");
		// else
		// {
		// 	current = (*head)->b;
		// 	printf("B is not NULL\n");
		// 	while (current->next)
		// 	{
		// 		printf("nbr = %d\n", current->value);
		// 		current = current->next;
		// 	}
		// 	printf("nbr = %d\n", current->value);
		// }
		// if ((*head)->a)
		// {
		// 	t_lst	*current;
		// 	current = (*head)->a;
		// 	printf("A is not NULL\n");
		// 	while (current->next)
		// 	{
		// 		printf("nbr = %d\n", current->value);
		// 		current = current->next;
		// 	}
		// 	printf("nbr = %d\n", current->value);
		// }
		// else
		// 	printf("A is NULL\n");
		
	}
	align_stack(head);
	// t_lst	*current;
	// if (!(*head)->b)
	// 	printf("B is NULL\n");
	// else
	// {
	// 	current = (*head)->b;
	// 	printf("B is not NULL\n");
	// 	while (current->next)
	// 	{
	// 		printf("nbr = %d\n", current->value);
	// 		current = current->next;
	// 	}
	// 	printf("nbr = %d\n", current->value);
	// }
	// if ((*head)->a)
	// {
	// 	t_lst	*current;
	// 	current = (*head)->a;
	// 	printf("A is not NULL\n");
	// 	while (current->next)
	// 	{
	// 		printf("nbr = %d\n", current->value);
	// 		current = current->next;
	// 	}
	// 	printf("nbr = %d\n", current->value);
	// }
	// else
	// 	printf("A is NULL\n");


}