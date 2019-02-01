/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:32:00 by djast             #+#    #+#             */
/*   Updated: 2019/02/01 14:49:22 by vurrigon         ###   ########.fr       */
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

static intmax_t	ft_recursive_power(intmax_t nb, intmax_t power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	return (nb * ft_recursive_power(nb, power - 1));
}

void		ft_putllnbr(uintmax_t n)
{
	unsigned int	size;
	uintmax_t	mno;

	size = ft_num_size(n) - 1;
	mno = ft_recursive_power(10, size);
	while (mno != 0)
	{
		ft_putchar(n / mno + 48);
		n %= mno;
		mno /= 10;
	}
}

static long long    ft_pow(long long nb, int pow)
{
    long long result;

	result = 1;
	if (pow == 0)
		return (1);
	else if (pow < 0)
		return (0);
	else
	{
		while (pow > 0)
		{
			result *= nb;
			pow--;
		}
		return (result);
	}
}

char    *ft_translation(uintmax_t value, int base)
{
    int        i;
    char    *nbr;

    i = 1;
    while ((uintmax_t)ft_pow(base, i) - 1 < value)
        i++;
    if (!(nbr = (char *)malloc(sizeof(nbr) * i)))
    	return (0);
    nbr[i] = '\0';
    while (i-- > 0)
    {
        nbr[i] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
        value = value / base;
    }
    return (nbr);
}

void	ft_upper_str(char *str)
{
	while (*str)
	{
		if (*str >= 97 && *str <= 122)
			*str = *str - 32;
		str++;
	}
}