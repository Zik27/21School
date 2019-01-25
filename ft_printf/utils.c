/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:32:00 by djast             #+#    #+#             */
/*   Updated: 2019/01/24 16:29:56 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	ft_num_size(intmax_t n)
{
	intmax_t	count;

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

void		ft_putllnbr(intmax_t n)
{
	intmax_t	size;
	intmax_t	mno;

	size = ft_num_size(n) - 1;
	mno = ft_recursive_power(10, size);
	n < 0 ? ft_putchar('-') : NULL;
	while (mno != 0)
	{
		ft_putchar(n > 0 ? n / mno + 48 : -(n / mno) + 48);
		n %= mno;
		mno /= 10;
	}
}

static uintmax_t	ft_num_size_u(uintmax_t n)
{
	intmax_t	count;

	count = 0;
	while ((n = n / 10) != 0)
		count++;
	return (count + 1);
}

void		ft_putllunbr(uintmax_t n)
{
	intmax_t	size;
	uintmax_t	mno;

	size = ft_num_size_u(n) - 1;
	mno = ft_recursive_power(10, size);
	while (mno != 0)
	{
		ft_putchar(n > 0 ? n / mno + 48 : -(n / mno) + 48);
		n %= mno;
		mno /= 10;
	}
}

static long long    ft_pow(int nb, int pow)
{
    if (pow == 0)
        return (1);
    else
        return (nb * ft_pow(nb, pow - 1));
}

char    *ft_translation(long long value, int base)
{
    int        i;
    char    *nbr;
    int        neg;

    i = 1;
    neg = 0;
    if (value < 0)
    {
        if (base == 10)
            neg = 1;
        value *= -1;
    }
    while (ft_pow(base, i) - 1 < value)
        i++;
    nbr = (char*)malloc(sizeof(nbr) * i);
    nbr[i + neg] = '\0';
    while (i-- > 0)
    {
        nbr[i + neg] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
        value = value / base;
    }
    if (neg)
        nbr[0] = '-';
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