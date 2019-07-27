/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_below_six.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:02:39 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:05:25 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	case_for_four(t_head **head)
{
	long int	smallest;
	int			flag;

	flag = 1;
	smallest = get_smallest((*head)->a);
	while (flag)
	{
		if (smallest == (*head)->a->value)
		{
			do_pb(head);
			flag = 0;
		}
		else
			do_ra(head);
	}
	sorting_below_four(head, 3);
	do_pa(head);
}

void	case_for_five(t_head **head)
{
	int	smallest;
	int	max;
	int	flag;

	flag = -2;
	smallest = get_smallest((*head)->a);
	max = get_max((*head)->a);
	while (flag)
	{
		if (smallest == (*head)->a->value || max == (*head)->a->value)
		{
			do_pb(head);
			flag++;
		}
		else
			do_ra(head);
	}
	sorting_below_four(head, 3);
	do_pa(head);
	if ((*head)->a->value == max)
		do_ra(head);
	do_pa(head);
	if ((*head)->a->value == max)
		do_ra(head);
}

void	sorting_below_six(t_head **head, int length)
{
	if (length == 4)
		case_for_four(head);
	else if (length == 5)
		case_for_five(head);
}
