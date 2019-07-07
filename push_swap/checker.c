/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:29:11 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/07 16:00:57 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	t_head *head;

// 	if (argc < 2)
// 		return (0);
// 	if (!valid(argv))
// 	{
// 		write(1, "Error\n", 6);
// 		return (0);
// 	}
// 	head = create_head(argv, 0);
// 	if (!read_command(&head))
// 	{
// 		write(1, "Error\n", 6);
// 		return (0);
// 	}





// 	t_lst	*current;
// 	if (!head->b)
// 		printf("B is NULL\n");
// 	else
// 	{
// 		current = head->b;
// 		printf("B is not NULL\n");
// 		while (current->next)
// 		{
// 			printf("nbr = %d\n", current->value);
// 			current = current->next;
// 		}
// 		printf("nbr = %d\n", current->value);
// 	}
// 	if (head->a)
// 	{
// 		t_lst	*current;
// 		current = head->a;
// 		printf("A is not NULL\n");
// 		while (current->next)
// 		{
// 			printf("nbr = %d\n", current->value);
// 			current = current->next;
// 		}
// 		printf("nbr = %d\n", current->value);
// 	}
// 	else
// 		printf("A is NULL\n");
// 	if (check_sort(head))
// 		write(1, "OK\n", 3);
// 	else
// 		write(1, "KO\n", 3);
// 	return (0);
// }





int	main(int argc, char **argv)
{
	t_head *head;
	int	len;

	if (argc < 2)
		return (0);
	if (!valid(argv))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	head = create_head(argv, 1);
	if (check_sort(head))
		return (0);
	len = get_len_stack(head->a);
	if (len < 4)
		sorting_below_four(&head, len);
	else if (len < 6)
		sorting_below_six(&head, len);
	// else if (len < 101)
	// 	sorting_below_hund(&head);
	// else
	// 	sorting_big(&head);
	t_lst	*current;
	if (!head->b)
		printf("B is NULL\n");
	else
	{
		current = head->b;
		printf("B is not NULL\n");
		while (current->next)
		{
			printf("nbr = %d\n", current->value);
			current = current->next;
		}
		printf("nbr = %d\n", current->value);
	}
	if (head->a)
	{
		t_lst	*current;
		current = head->a;
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
	return (0);
}
