/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_more_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:44:50 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/21 20:19:51 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int		check_marks(t_lst *a)
{
	while (a)
	{
		if (!a->mark)
			return (1);
		a = a->next;
	}
	return (0);
}

int		get_len_increasing_seq(t_head **head, t_lst **a, int do_mark)
{
	int		len;
	t_lst	*tmp;
	int		val;

	len = 1;
	val = (*a)->value;
	(*a)->mark = do_mark ? 1 : (*a)->mark;
	tmp = !(*a)->next ? (*head)->a : (*a)->next;
	while (tmp != *a)
	{
		//printf("TMP = %d\n", tmp->value);
		if (tmp->value > val)
		{
			val = tmp->value;
			if (do_mark)
				tmp->mark = 1;
			len++;
		}
		if (!tmp->next)
			tmp = (*head)->a;
		else
			tmp = tmp->next;
	}
	return (len);
}

int		check_swap(t_head **head, int max)
{
	t_lst	*a;
	int		current_len;

	a = (*head)->a;
	swap_value(&((*head)->a->value), &((*head)->a->next->value));
	while (a)
	{
		current_len = get_len_increasing_seq(head, &a, 0);
		//printf("CUR_LEN ==== %d\n", current_len);
		if (current_len > max)
		{
			// t_lst *cur;
			// cur = (*head)->a;
			// while (cur)
			// {
			// 	//printf("VALUE == %d\n", cur->value);
			// 	cur = cur->next;
			// }
			// cur = (*head)->a;
			// while (cur)
			// {
			// 	//printf("NEW_VALUE == %d\n", cur->value);
			// 	cur = cur->next;
			// }
			swap_value(&((*head)->a->value), &((*head)->a->next->value));
			return (1);
		}
		a = a->next;
	}
	swap_value(&((*head)->a->value), &((*head)->a->next->value));
	return (0);

}

int	markup(t_head **head)
{
	t_lst	*a;
	t_lst	*begin_max;
	int		len;
	int		max;

	a = (*head)->a;
	len = 0;
	max = 0;
	while (a)
	{
		len = get_len_increasing_seq(head, &a, 0);
		//printf("Value ======= %d, RESULT ======== %d\n", a->value, len);
		if (len > max)
		{
			max = len;
			begin_max = a;
		}
		a = a->next;
	}
	get_len_increasing_seq(head, &begin_max, 1);
	t_lst	*current;
	current = (*head)->a;
	while (current)
	{	
		printf("ISXODNOE == %d, Mark = %d\n", current->value, current->mark);
		current = current->next;
	}
	printf("MAX = %d\n", max);
	return (max);
}

void	zeroing_marks(t_head **head)
{
	t_lst	*a;

	a = (*head)->a;

	while (a)
	{
		a->mark = 0;
		a = a->next;
	}
}

void	sorting_more_six(t_head **head)
{
	int		max;

	max = markup(head);
	while (check_marks((*head)->a))
	{
		// cur = (*head)->a;
		// while (cur)
		// {
		// 	printf("VALUE == %d, mark == %d\n", cur->value, cur->mark);
		// 	cur = cur->next;
		// }
		if (check_swap(head, max))
		{
			do_sa(head);
			zeroing_marks(head);
			// cur = (*head)->a;
			// while (cur)
			// {
			// 	printf("VALUE == %d, mark == %d\n", cur->value, cur->mark);
			// 	cur = cur->next;
			// }
			max = markup(head);
			// cur = (*head)->a;
			// while (cur)
			// {
			// 	printf("NEEEEEW_VALUE == %d, mark == %d\n", cur->value, cur->mark);
			// 	cur = cur->next;
			// }
		}
		if ((*head)->a->mark)
			do_ra(head);
		else
			do_pb(head);
	}
	main_sorting(head);






	t_lst	*current;
	printf("==================================\n");
	if (!(*head)->b)
		printf("B is NULL\n");
	else
	{
		current = (*head)->b;
		printf("B is not NULL\n");
		while (current->next)
		{
			printf("nbr = %d\n", current->value);
			current = current->next;
		}
		printf("nbr = %d\n", current->value);
	}
	if ((*head)->a)
	{
		t_lst	*current;
		current = (*head)->a;
		printf("A is not NULL\n");
		while (current->next)
		{
			printf("nbr = %d\n", current->value);
			current = current->next;
		}
		printf("nbr = %d\n", current->value);
	}
	else
		printf("A is NULL\n");

}