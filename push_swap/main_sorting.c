/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:49:36 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/21 20:19:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
int		check_stack_b(t_lst *elem, t_head *head)
{
	int		index;
	int		len_b;
	t_lst	*b;

	index = 0;
	len_b = get_len_stack(head->b);
	b = head->b;
	while (elem != b)
	{
		index++;
		b = b->next;
	}
	if (index > len_b - index)
		index = len_b - index;
	printf("INDEX === %d\n", ++index);
	return (index + 1);
}

int		check_count_op(t_lst *elem, t_head *head)
{
	int	count;
	int	value;
	t_lst	*a;

	check_stack_b(elem, head);
	value = elem->value;
	count = 0;
	a = head->a;
	// while (a)
	// {

	// }
	return (0);


}

void	main_sorting(t_head **head)
{
	t_lst *a;
	t_lst *b;

	a = (*head)->a;
	b = (*head)->b;
	printf("=========================================\n");
	while (b)
	{
		check_count_op(b, *head);
		b = b->next;
	}

}