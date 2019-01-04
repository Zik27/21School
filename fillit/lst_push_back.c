/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:12:23 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/04 16:29:50 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	free_lst(tetriminos_fig **head)
{
	tetriminos_fig *tmp;
	tetriminos_fig *delete_tmp;

	delete_tmp = *head;
	while (delete_tmp)
	{
		tmp = delete_tmp->next;
		free(delete_tmp->data);
		free(delete_tmp);
		delete_tmp = tmp;
	}
	*head = NULL;
}

int		*ft_intdup(int const *src)
{
	int *dup;

	if (!(dup = (int *)malloc(3 * sizeof(int))))
		return (NULL);
	ft_memcpy(dup, src, 3 * sizeof(int));
	return (dup);
}

tetriminos_fig	*ft_create_elem(int *data)
{
	tetriminos_fig	*list;

	if ((list = malloc(sizeof(tetriminos_fig))))
	{
		if (!(list->data = ft_intdup(data)))
			return (NULL);
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

int	lst_push_back(tetriminos_fig **head, int *data)
{
	tetriminos_fig	*current;

	if (*head)
	{
		current = *head;
		while (current->next)
			current = current->next;
		if (!(current->next = ft_create_elem(data)))
			return (0);
	}
	else
		if (!(*head = ft_create_elem(data)))
			return (0);
	return (1);
}