/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:10:12 by djast             #+#    #+#             */
/*   Updated: 2019/02/04 14:39:15 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_percent(char percent, t_qual *qual)
{
	char	width_char;
	int		real_width;

	if (qual->minus == 0)
	{
		width_char = qual->zero == 0 ? ' ' : '0';
		real_width = qual->width - 1;
		while (real_width-- > 0)
			write(1, &width_char, 1);
		write(1, &percent, 1);
	}
	else
	{
		write(1, &percent, 1);
		width_char = ' ';
		real_width = qual->width - 1;
		while (real_width-- > 0)
			write(1, &width_char, 1);
	}
	return (ft_max(2, 1, qual->width));
}
