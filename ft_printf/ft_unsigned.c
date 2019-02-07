/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:02:41 by djast             #+#    #+#             */
/*   Updated: 2019/02/07 15:43:30 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	ft_size_by_lenght_u(uintmax_t nbr, t_qual *qual)
{
	if (ft_strcmp(QL, "ll") == 0)
		nbr = (unsigned long long)nbr;
	else if (ft_strcmp(QL, "l") == 0)
		nbr = (unsigned long)nbr;
	else if (ft_strcmp(QL, "h") == 0)
		nbr = (unsigned short int)nbr;
	else if (ft_strcmp(QL, "hh") == 0)
		nbr = (unsigned char)nbr;
	else if (ft_strcmp(QL, "j") == 0)
		nbr = (uintmax_t)nbr;
	else if (ft_strcmp(QL, "z") == 0)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

int					ft_u(uintmax_t nbr, t_qual *qual)
{
	int size_nbr;

	nbr = ft_size_by_lenght_u(nbr, qual);
	QUS = 1;
	QSN = 0;
	size_nbr = ft_num_size(nbr);
	if (QM == 0)
	{
		ft_print_width(qual, size_nbr);
		ft_print_presicion(qual, size_nbr);
		if (nbr != 0 || QPR != 0)
			ft_putllnbr(nbr);
		if (nbr == 0 && QW != -1 && QPR == 0)
			write(1, " ", 1);
	}
	else
	{
		ft_print_presicion(qual, size_nbr);
		if (nbr != 0 || QPR != 0)
			ft_putllnbr(nbr);
		ft_print_width(qual, size_nbr);
	}
	return (QPR == 0 && nbr == 0 ? 0 :
	ft_max(3, QW, QPR, size_nbr));
}
