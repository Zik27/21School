/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_more_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:44:50 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/26 15:04:12 by vurrigon         ###   ########.fr       */
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

int	markup(t_head **head, int do_marks)
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
		if (len > max || (len == max && begin_max->value > a->value))
		{
			max = len;
			begin_max = a;
		}
		a = a->next;
	}
	if (do_marks)
		get_len_increasing_seq(head, &begin_max, 1);
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

int		check_swap(t_head **head, int max)
{
	t_lst	*a;
	int		current_len;
	//int		current_len_ind;

	a = (*head)->a;
	swap_value(&((*head)->a->value), &((*head)->a->next->value));
	while (a)
	{
		current_len = get_len_increasing_seq(head, &a, 0);
		//current_len_ind = get_max_mark_index(a, head);
		//printf("len_index %d, len_greate %d\n", current_len_ind, current_len);
		//printf("CUR_LEN ==== %d\n", current_len);
		if (current_len > max)
		{
			swap_value(&((*head)->a->value), &((*head)->a->next->value));
			return (1);
		}
		a = a->next;
	}
	swap_value(&((*head)->a->value), &((*head)->a->next->value));
	return (0);

}

void	sorting_more_six(t_head **head)
{
	int		max;
	// int		len_index;
	// int		len;
	//t_lst	*cur;

	max = markup(head, 1);
	//printf("MAX === %d\n", max);
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
			//printf("max === %d\n", max);
			do_sa(head);
			zeroing_marks(head);
			// cur = (*head)->a;
			// while (cur)
			// {
			// 	printf("VALUE == %d, mark == %d\n", cur->value, cur->mark);
			// 	cur = cur->next;
			// }
			max = markup(head, 1);
			// len_index = markup_by_index(head, 0);
			// if (len > len_index)
			// 	max = markup(head, 1);
			// else
			// 	max = markup_by_index(head, 1);
			// cur = (*head)->a;
			// while (cur)
			// {
			// 	printf("NEEEEEW_VALUE == %d, mark == %d\n", cur->value, cur->mark);
			// 	cur = cur->next;
			// }
		}
		else if (!(*head)->a->mark)
			do_pb(head);
		else
			do_ra(head);
			
	}
	main_sorting(head);
}