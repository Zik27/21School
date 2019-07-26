/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:27:47 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/24 16:56:33 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	solver(t_head **head, t_lst *stack_min)
{
	int	tmp_a;
	int	tmp_b;

	tmp_a = stack_min->count_op_a;
	tmp_b = stack_min->count_op_b;
	//printf("value === %d, A = %d, B = %d\n", stack_min->value, stack_min->count_op_a, stack_min->count_op_b);
	if (tmp_a < 0 && tmp_b < 0)
		while (tmp_a && tmp_b)
		{
			tmp_a++;
			tmp_b++;
			do_rrr(head);
		}
	else if (tmp_a > 0 && tmp_b > 0)
		while (tmp_a && tmp_b)
		{
			tmp_a--;
			tmp_b--;
			do_rr(head);
		}
	if (tmp_b > 0)
		while (tmp_b--)
			do_rb(head);
	else if (tmp_b < 0)
		while (tmp_b++)
			do_rrb(head);
	if (tmp_a > 0)
		while (tmp_a--)
			do_ra(head);
	else if (tmp_a < 0)
		while (tmp_a++)
			do_rra(head);
	do_pa(head);
}
