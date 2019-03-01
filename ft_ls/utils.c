/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:52:06 by djast             #+#    #+#             */
/*   Updated: 2019/03/01 15:03:07 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_struct(t_ls *ls)
{
	if (ls->is_reversed) 
		ft_printf(GREEN);
	else 
		ft_printf(RED);
	ft_printf("is_reversed: %d\n", ls->is_reversed);
	ft_printf(RESET);
	if (ls->is_recursive) 
		ft_printf(GREEN);
	else 
		ft_printf(RED);
	ft_printf("is_recursive: %d\n", ls->is_recursive);
	ft_printf(RESET);
	if (ls->is_with_dot) 
		ft_printf(GREEN);
	else 
		ft_printf(RED);
	ft_printf("is_with_dot: %d\n", ls->is_with_dot);
	ft_printf(RESET);
	if (ls->is_sort_by_time) 
		ft_printf(GREEN);
	else 
		ft_printf(RED);
	ft_printf("is_sort_by_time: %d\n", ls->is_sort_by_time);
	ft_printf(RESET);
	if (ls->long_format) 
		ft_printf(GREEN);
	else 
		ft_printf(RED);
	ft_printf("long_format: %d\n", ls->long_format);
	ft_printf(RESET);
	if (ls->path != NULL) 
		ft_printf(GREEN);
	else 
		ft_printf(RED);
	ft_printf("path: %s\n", ls->path);
	ft_printf(RESET);
}
