/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:27:47 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 16:19:18 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	optimization(t_head **head, int *count_a, int *count_b)
{
	if (*count_a < 0 && *count_b < 0)
		while (*count_a && *count_b)
		{
			(*count_a)++;
			(*count_b)++;
			do_rrr(head);
		}
	else if (*count_a > 0 && *count_b > 0)
		while (*count_a && *count_b)
		{
			(*count_a)--;
			(*count_b)--;
			do_rr(head);
		}
}

void	solver(t_head **head, t_lst *stack_min)
{
	int	tmp_a;
	int	tmp_b;

	tmp_a = stack_min->count_op_a;
	tmp_b = stack_min->count_op_b;
	optimization(head, &tmp_a, &tmp_b);
	if (tmp_a > 0)
		while (tmp_a--)
			do_ra(head);
	else if (tmp_a < 0)
		while (tmp_a++)
			do_rra(head);
	if (tmp_b > 0)
		while (tmp_b--)
			do_rb(head);
	else if (tmp_b < 0)
		while (tmp_b++)
			do_rrb(head);
	do_pa(head);
}
