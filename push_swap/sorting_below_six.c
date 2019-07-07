/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_below_six.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:02:39 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/07 17:14:47 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sorting_below_six(t_head **head, int length)
{
	do_pb(head);
	if (length == 5)
		do_pb(head);
}
