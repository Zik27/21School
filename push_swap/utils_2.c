/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:12:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:22:17 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_lst	*get_next_min(t_lst *stack)
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

void			zeroing_marks(t_head **head)
{
	t_lst	*a;

	a = (*head)->a;
	while (a)
	{
		a->mark = 0;
		a = a->next;
	}
}

void			indexing(t_head **head)
{
	t_lst	*current;
	int		index;

	index = 1;
	while ((current = get_next_min((*head)->a)))
		current->index = index++;
}

void			align_stack(t_head **head)
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

void			do_rr(t_head **head)
{
	int	writer;

	writer = (*head)->do_write;
	(*head)->do_write = 0;
	do_ra(head);
	do_rb(head);
	(*head)->do_write = writer;
	if ((*head)->do_write)
		write(1, "rr\n", 3);
	(*head)->operation = "rr";
}
