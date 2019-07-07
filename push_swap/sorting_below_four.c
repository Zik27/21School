/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_below_four.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:10:36 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/07 17:16:12 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	sorting_case_one(t_head **head)
{
	do_sa(head);
}

void	sorting_case_two(t_head **head)
{
	do_sa(head);
	do_rra(head);
}

void	sorting_case_three(t_head **head)
{
	do_ra(head);
}

void	sorting_case_five(t_head **head)
{
	do_rra(head);
}

void	sorting_case_four(t_head **head)
{
	do_sa(head);
	do_ra(head);
}

void	sorting_below_four(t_head **head, int length)
{
	t_lst *a;

	a = (*head)->a;
	if (length == 2)
		sorting_case_one(head);
	else if (length == 3)
	{
		if (a->value > a->next->value &&  a->next->value > a->next->next->value)
			sorting_case_two(head);
		else if (a->value > a->next->value && a->value > a->next->next->value)
			sorting_case_three(head);
		else if (a->value > a->next->value)
			sorting_case_one(head);
		else if (a->value > a->next->next->value)
			sorting_case_five(head);
		else
			sorting_case_four(head);
	}
}