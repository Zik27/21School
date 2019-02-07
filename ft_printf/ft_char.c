/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:01:33 by djast             #+#    #+#             */
/*   Updated: 2019/02/07 15:43:20 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_c(char str, t_qual *qual)
{
	int	real_width;

	real_width = QW;
	if (QM)
	{
		write(1, &str, 1);
		while (real_width-- > 1)
			write(1, " ", 1);
	}
	else
	{
		if (QZ)
			while (real_width-- > 1)
				write(1, "0", 1);
		while (real_width-- > 1)
			write(1, " ", 1);
		write(1, &str, 1);
	}
	return (QW > 1 ? QW : 1);
}
