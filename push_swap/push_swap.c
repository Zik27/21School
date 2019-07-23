/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 13:37:45 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/23 16:55:27 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_head *head;
	int	len;

	if (argc < 2)
		return (0);
	else if (argc == 2 && ft_strrchr(argv[1], ' '))
		argv = ft_strsplit(argv[1], ' ');
	if (!valid(argv))
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	head = create_head(argv, 1);
	if (check_sort(head))
		exit(0);
	len = get_len_stack(head->a);
	if (len < 4)
		sorting_below_four(&head, len);
	else if (len < 6)
		sorting_below_six(&head, len);
	else
		sorting_more_six(&head);

	// t_lst	*current;
	// if (!head->b)
	// 	printf("B is NULL\n");
	// else
	// {
	// 	current = head->b;
	// 	printf("B is not NULL\n");
	// 	while (current->next)
	// 	{
	// 		printf("nbr = %d\n", current->value);
	// 		current = current->next;
	// 	}
	// 	printf("nbr = %d\n", current->value);
	// }
	// if (head->a)
	// {
	// 	t_lst	*current;
	// 	current = head->a;
	// 	printf("A is not NULL\n");
	// 	while (current->next)
	// 	{
	// 		printf("nbr = %d\n", current->value);
	// 		current = current->next;
	// 	}
	// 	printf("nbr = %d\n", current->value);
	// }
	// else
	// 	printf("A is NULL\n");
	exit(0);
}