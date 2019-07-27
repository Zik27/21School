/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:29:11 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:29:08 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_head *head;

	if (argc < 2)
		return (0);
	argc = ft_strcmp(argv[1], "-v") == 0 ? 1 : 0;
	argv = argc ? &argv[2] : &argv[1];
	if (ft_strrchr(argv[0], ' '))
		argv = ft_strsplit(argv[0], ' ');
	if (!valid(argv))
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	head = create_head(argv, 0, argc, 0);
	if (!read_command(&head))
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	if (check_sort(head))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	exit(0);
}
