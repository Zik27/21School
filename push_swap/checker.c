/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:29:11 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/13 18:16:50 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_head *head;

	if (!valid(argv, argc))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	head = create_head(argv);
	// if (!reader())
	// {
	// 	write(1, "Error\n", 6);
	// 	return (0);
	// }
	return (0);

}
