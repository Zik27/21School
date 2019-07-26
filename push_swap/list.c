/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:47:56 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/26 16:33:51 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	delete_last_elem(t_lst **list)
{
	t_lst *current;
	t_lst *before;

	current = *list;
	while (current->next)
	{
		if (!current->next->next)
			before = current;
		current = current->next;
	}
	free(current);
	before->next = NULL;
}

t_lst	*ft_create_elem(int data, int mark, int index)
{
	t_lst	*list;

	if ((list = (t_lst *)malloc(sizeof(t_lst))))
	{
		list->value = data;
		list->mark = mark;
		list->count_op_a = 0;
		list->count_op_b = 0;
		list->sum_step = 0;
		list->index = index;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

t_lst	*create_lst(char **data)
{
	t_lst	*head;
	t_lst	*current;
	int		i;

	i = ft_strcmp(data[0], "-v") == 0 ? 1 : 0;
	if (!(head = (t_lst *)malloc(sizeof(t_lst))))
		return (0);
	head->value = ft_atoi(data[i++]);
	head->mark = 0;
	head->count_op_a = 0;
	head->count_op_b = 0;
	head->sum_step = 0;
	head->index = 0;
	head->next = NULL;
	current = head;
	while (data[i])
	{
		current->next = ft_create_elem(ft_atoi(data[i++]), 0, 0);
		current = current->next;
	}
	return (head);
}

t_head	*create_head(char **data, int write, int do_debug)
{
	t_head	*head;

	if ((head = malloc(sizeof(t_head))))
	{
		head->a = create_lst(data);
		head->b = NULL;
		head->do_write = write;
		head->do_debug = do_debug;
		return (head);
	}
	return (NULL);
}