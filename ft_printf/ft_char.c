/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:01:33 by djast             #+#    #+#             */
/*   Updated: 2019/02/01 18:28:38 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_c(char str, t_qual *qual)
{
	int	real_width;

	real_width = qual->width;
	if (qual->minus)
	{
		write(1, &str, 1);
		while (real_width-- > 1)
			write(1, " ", 1);
	}
	else
	{
		if (qual->zero)
			while (real_width-- > 1)
				write(1, "0", 1);
		while (real_width-- > 1)
			write(1, " ", 1);
		write(1, &str, 1);
	}
	return (qual->width > 1 ? qual->width : 1);
}
