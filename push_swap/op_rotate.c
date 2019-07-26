/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:33:52 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/26 16:43:05 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	do_rra(t_head **head)
{
	t_lst	*a;
	t_lst	*new;

	a = (*head)->a;
	new = NULL;
	if (a && a->next)
	{
		while (a->next)
			a = a->next;
		new = ft_create_elem(a->value, a->mark, a->index);
		delete_last_elem(&((*head)->a));
		new->next = (*head)->a;
		(*head)->a = new;
		if ((*head)->do_write)
			write(1, "rra\n", 4);
	}
}

void	do_rrb(t_head **head)
{
	t_lst	*b;
	t_lst	*new;

	b = (*head)->b;
	new = NULL;
	if (b && b->next)
	{
		while (b->next)
			b = b->next;
		new = ft_create_elem(b->value, b->mark, b->index);
		delete_last_elem(&((*head)->b));
		new->next = (*head)->b;
		(*head)->b = new;
		if ((*head)->do_write)
			write(1, "rrb\n", 4);
	}
}

void	do_rrr(t_head **head)
{
	int	writer;

	writer = (*head)->do_write;
	(*head)->do_write = 0;
	do_rra(head);
	do_rrb(head);
	(*head)->do_write = writer;
	if ((*head)->do_write)
		write(1, "rrr\n", 4);
}

void	do_ra(t_head **head)
{
	t_lst	*a;
	t_lst	*new;

	a = (*head)->a;
	new = NULL;
	if (a && a->next)
	{
		new = ft_create_elem(a->value, a->mark, a->index);
		while (a->next)
			a = a->next;
		a->next = new;
		a = (*head)->a;
		new = a;
		a = a->next;
		free(new);
		(*head)->a = a;
		if ((*head)->do_write)
			write(1, "ra\n", 3);
	}
}

void	do_rb(t_head **head)
{
	t_lst	*b;
	t_lst	*new;

	b = (*head)->b;
	new = NULL;
	if (b && b->next)
	{
		new = ft_create_elem(b->value, b->mark, b->index);
		while (b->next)
			b = b->next;
		b->next = new;
		b = (*head)->b;
		new = b;
		b = b->next;
		free(new);
		(*head)->b = b;
		if ((*head)->do_write)
			write(1, "rb\n", 3);
	}

}

void	do_rr(t_head **head)
{
	int	writer;

	writer = (*head)->do_write;
	(*head)->do_write = 0;
	do_ra(head);
	do_rb(head);
	(*head)->do_write = writer;
	if ((*head)->do_write)
		write(1, "rr\n", 3);
}
