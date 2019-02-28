/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:32:00 by djast             #+#    #+#             */
/*   Updated: 2019/02/08 18:56:01 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int		ft_num_size(uintmax_t n)
{
	unsigned int	count;

	count = 0;
	while ((n = n / 10) != 0)
		count++;
	return (count + 1);
}

static intmax_t		ft_recursive_power(intmax_t nb, intmax_t power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	return (nb * ft_recursive_power(nb, power - 1));
}

void				ft_putllnbr(uintmax_t n)
{
	unsigned int	size;
	uintmax_t		mno;

	size = ft_num_size(n) - 1;
	mno = ft_recursive_power(10, size);
	while (mno != 0)
	{
		ft_putchar(n / mno + 48);
		n %= mno;
		mno /= 10;
	}
}

char				*ft_translation(uintmax_t value, int base)
{
	int			i;
	char		*nbr;

	i = 1;
	while ((uintmax_t)ft_recursive_power(base, i) - 1 < value)
		i++;
	if (!(nbr = (char *)malloc(sizeof(nbr) * i)))
		exit(1);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	return (nbr);
}

char				*check_modifier(intmax_t numb, int base, t_qual *qual)
{
	char	*result_str;

	if (ft_strcmp(QL, "l") == 0)
		result_str = ft_translation((unsigned long int)numb, base);
	else if (ft_strcmp(QL, "ll") == 0)
		result_str = ft_translation((unsigned long long int)numb, base);
	else if (ft_strcmp(QL, "j") == 0)
		result_str = ft_translation(numb, base);
	else if (ft_strcmp(QL, "h") == 0)
		result_str = ft_translation((unsigned short int)numb, base);
	else if (ft_strcmp(QL, "hh") == 0)
		result_str = ft_translation((unsigned char)numb, base);
	else if (ft_strcmp(QL, "z") == 0)
		result_str = ft_translation((size_t)numb, base);
	else
		result_str = ft_translation((unsigned int)numb, base);
	return (result_str);
}
