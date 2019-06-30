/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:37:13 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/30 18:22:19 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	read_command(t_head **head)
{
	char	*line;

	while (get_next_line(0, &line) == 1)
	{
		if (!ft_strcmp(line, "sa"))
			do_sa(head);
		else if (!ft_strcmp(line, "sb"))
			do_sb(head);
		else if (!ft_strcmp(line, "ss"))
			do_ss(head);
		else if (!ft_strcmp(line, "pa"))
			do_pa(head);
		else if (!ft_strcmp(line, "pb"))
			do_pb(head);
		
		// else if (!ft_strcmp(line, "ra"))
		// 	do_pb(head);
		// else if (!ft_strcmp(line, "rb"))
		// 	do_pb(head);
		// else if (!ft_strcmp(line, "rr"))
		// 	do_pb(head);
		// else if (!ft_strcmp(line, "rra"))
		// 	do_pb(head);
		// else if (!ft_strcmp(line, "rrb"))
		// 	do_pb(head);
		// else if (!ft_strcmp(line, "rrr"))
		// 	do_pb(head);
		else
			return (0);
	}
	return (1);
}
