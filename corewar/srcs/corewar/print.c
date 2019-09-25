/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:20:31 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 13:47:37 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cerror(char *message, char *error_file)
{
	ft_printf(message, error_file);
	ft_printf("\n");
	exit(-1);
}

void	print_help(char **argv)
{
	ft_printf("Usage: ");
	ft_printf("%s [-dump nbr_cycles] [[-n number] champion1.cor] ...\n", argv[0]);
}