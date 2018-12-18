/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:12:56 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:11:02 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*begin;
	t_list	*tmp;

	begin = *alst;
	while (begin)
	{
		tmp = begin->next;
		del(begin->content, begin->content_size);
		free(begin);
		begin = tmp;
	}
	*alst = NULL;
}
