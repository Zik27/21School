/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 13:37:45 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:03:58 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_head	*head;
	int		len;

	if (argc < 2)
		return (0);
	argv = &argv[1];
	if (ft_strrchr(argv[0], ' '))
		argv = ft_strsplit(argv[0], ' ');
	if (!valid(argv))
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	head = create_head(argv, 1, 0, argc);
	if (check_sort(head))
		exit(0);
	len = get_len_stack(head->a);
	if (len < 4)
		sorting_below_four(&head, len);
	else if (len < 6)
		sorting_below_six(&head, len);
	else
		sorting_more_six(&head);
	exit(0);
}
