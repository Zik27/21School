/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:06:00 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:06:37 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sorting_case_one(t_head **head)
{
	do_sa(head);
}

void	sorting_case_two(t_head **head)
{
	do_sa(head);
	do_rra(head);
}

void	sorting_case_three(t_head **head)
{
	do_ra(head);
}

void	sorting_case_five(t_head **head)
{
	do_rra(head);
}

void	sorting_case_four(t_head **head)
{
	do_sa(head);
	do_ra(head);
}
