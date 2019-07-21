/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:29:11 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/21 15:48:08 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_head *head;

	if (argc < 2)
		return (0);
	else if (argc == 2 && ft_strrchr(argv[1], ' '))
		argv = ft_strsplit(argv[1], ' ');
	if (!valid(argv))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	head = create_head(argv, 0);
	if (!read_command(&head))
	{
		write(1, "Error\n", 6);
		return (0);
	}





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
	if (check_sort(head))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	exit(1);
	return (0);
}






