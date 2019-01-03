/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:12:23 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/03 21:02:56 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

tetriminos_fig	*ft_create_elem(int *data)
{
	tetriminos_fig	*list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->data[0] = data[0];
		list->data[1] = data[1];
		list->data[2] = data[2];
		list->next = NULL;
	}
	return (list);
}

void	lst_push_back(tetriminos_fig **head, int *data)
{
	tetriminos_fig	*current;

	if (*head)
	{
		current = *head;
		while (current->next)
		{
			printf("%d\n", current->data[0]);
			printf("%d\n", current->data[1]);
			printf("%d\n", current->data[2]);
			printf("\n");
			current = current->next;
		}
		current->next = ft_create_elem(data);
	}
	else
		*head = ft_create_elem(data);
}