/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:47:56 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/13 18:27:09 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_head	*create_head(char **data)
{
	t_head	*head;

	if ((head = malloc(sizeof(t_head))))
	{
		head->a = create_a(data);
		head->b = NULL;
		return (head);
	}
	return (NULL);
}