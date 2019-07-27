/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_below_four.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:10:36 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:08:29 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sorting_below_four(t_head **head, int length)
{
	t_lst *a;

	a = (*head)->a;
	if (length == 2)
		sorting_case_one(head);
	else if (length == 3)
	{
		if (a->value > a->next->value && a->next->value > a->next->next->value)
			sorting_case_two(head);
		else if (a->value > a->next->value && a->value > a->next->next->value)
			sorting_case_three(head);
		else if (a->value > a->next->value)
			sorting_case_one(head);
		else if (a->value > a->next->next->value)
			sorting_case_five(head);
		else if (a->next->next->value > a->value && a->next->value >
			a->next->next->value)
			sorting_case_four(head);
	}
}
