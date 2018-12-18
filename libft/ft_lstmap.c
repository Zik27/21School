/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:46:45 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:14:08 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*current;

	if (!lst)
		return (NULL);
	begin = f(lst);
	if (!begin)
		return (NULL);
	current = begin;
	while (lst->next)
	{
		lst = lst->next;
		current->next = f(lst);
		if (!current->next)
			return (NULL);
		current = current->next;
	}
	return (begin);
}
