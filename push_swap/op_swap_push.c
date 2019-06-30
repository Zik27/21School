/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:15:41 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/30 18:21:57 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_sa(t_head **head)
{
	t_lst	*a;
	int		tmp;

	a = (*head)->a;
	if (a && a->next)
	{
		tmp = a->value;
		a->value = a->next->value;
		a->next->value = tmp;
	}
}

void	do_sb(t_head **head)
{
	t_lst	*b;
	int		tmp;

	b = (*head)->b;
	if (b && b->next)
	{
		tmp = b->value;
		b->value = b->next->value;
		b->next->value = tmp;
	}
}

void	do_ss(t_head **head)
{
	do_sa(head);
	do_sb(head);
}

void	do_pa(t_head **head)
{
	t_lst *a;
	t_lst *b;
	t_lst *new;

	a = (*head)->a;
	b = (*head)->b;
	if (b)
	{
		new = ft_create_elem(b->value);
		new->next = a;
		(*head)->a = new;
		if (b->next)
			(*head)->b = b->next;
		else
			(*head)->b = NULL;
		free(b);
	}
}

void	do_pb(t_head **head)
{
	t_lst *a;
	t_lst *b;
	t_lst *new;

	a = (*head)->a;
	b = (*head)->b;
	if (a)
	{
		new = ft_create_elem(a->value);
		new->next = b;
		(*head)->b = new;
		if (a->next)
			(*head)->a = a->next;
		else
			(*head)->a = NULL;
		free(a);
	}
}