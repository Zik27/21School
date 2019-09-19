/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:53:24 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/19 17:24:41 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	error_file(char *str, int col, int row)
{
	ft_printf("[%d:%d] %s\n", row, col, str);
	exit(1);
}
