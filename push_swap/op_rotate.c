/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:33:52 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/07 17:14:13 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	do_rra(t_head **head)
{
	t_lst	*a;
	t_lst	*new;
	int		end;

	a = (*head)->a;
	new = NULL;
	end = 0;
	if (a && a->next)
	{
		while (a->next)
			a = a->next;
		end = a->value;
		delete_last_elem(&((*head)->a));
		new = ft_create_elem(end);
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
	int		end;

	b = (*head)->b;
	new = NULL;
	end = 0;
	if (b && b->next)
	{
		while (b->next)
			b = b->next;
		end = b->value;
		delete_last_elem(&((*head)->b));
		new = ft_create_elem(end);
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
	int		begin;

	a = (*head)->a;
	new = NULL;
	begin = 0;
	if (a && a->next)
	{
		begin = a->value;
		new = a;
		a = a->next;
		free(new);
		(*head)->a = a;
		while (a->next)
			a = a->next;
		new = ft_create_elem(begin);
		a->next = new;
		if ((*head)->do_write)
			write(1, "ra\n", 3);
	}
}

void	do_rb(t_head **head)
{
	t_lst	*b;
	t_lst	*new;
	int		begin;

	b = (*head)->b;
	new = NULL;
	begin = 0;
	if (b && b->next)
	{
		begin = b->value;
		new = b;
		b = b->next;
		free(new);
		(*head)->b = b;
		while (b->next)
			b = b->next;
		new = ft_create_elem(begin);
		b->next = new;
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
