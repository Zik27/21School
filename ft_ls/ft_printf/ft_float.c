/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:03:09 by djast             #+#    #+#             */
/*   Updated: 2019/02/11 12:17:59 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*int_to_bin(unsigned long long int nbr, char *s, int my_exp)
{
	unsigned long long int copy_nbr;
	int copy_exp;

	copy_nbr = nbr;
	copy_exp = my_exp;
	while ((copy_nbr = copy_nbr / 2) != 0)
		s++;
	while (copy_exp++ < -1)
		s++;
	s++;
	while (nbr != 0)
	{
		s--;
		*s = nbr % 2 == 0 ? '0' : '1';
		nbr /= 2;
	}
	while (my_exp++ < -1)
		s--;
	return (s);
}

char			*add_precision(char *ans, t_qual *qual)
{
	int		real_precision;
	char	*tmp;

	qual->precision = qual->precision == -1 ? 6 : qual->precision;
	if (ft_fract_size(ans) > qual->precision)
	{
		if (qual->precision == 0)
		{
			tmp = ans;
			ans = ft_strsub(ans, 0, ft_int_size(ans));
			free(tmp);
			return (ans);
		}
		else
		{
			tmp = ans;
			ans = ft_strsub(ans, 0, ft_int_size(ans) + 1 + qual->precision + 1);
			free(tmp);

			ans = round_fract(ans);
		}
	}
	real_precision = qual->precision - ft_fract_size(ans) + 1;
	while (real_precision-- > 0)
		ans = ft_strjoin(ans, "0");
	return (ans);
}

char			*add_width(char *ans, t_qual *qual)
{
	char	print_char;
	int		real_width;
	char	*str;
	int		dot;

	str = ft_strnew(1);
	ans = QPL == 1 && (QZ == 0 || QM == 1) && QSN == 0 ? ft_strjoin("+", ans) : ans;
	print_char = QZ == 1 && QM == 0 ? '0' : ' ';
	dot = QPR == 0 ? 0 : 1;
	if (QSN == 0 && QSP == 1 && QPL == 0)
		real_width = QW - (QPR + ft_int_size(ans) + dot + QSP);
	else
		real_width = QW - (QPR + ft_int_size(ans) + dot);
	while (real_width-- > 0)
	{
		*str = print_char;
		if (QSN == 1 && print_char == '0')
			ans = ft_strjoin("-", ft_strjoin(str,
				ft_strsub(ans, 1, ft_strlen(ans))));
		else
			ans = QM == 0 ? ft_strjoin(str, ans) : ft_strjoin(ans, str);
	}
	ans = QSP == 1 && QSN == 0 && QPL == 0 ? ft_strjoin(" ", ans) : ans;
	ans = QPL == 1 && QSN == 0 && QZ == 1 && QM == 0? ft_strjoin("+", ans) : ans;
	return (ans);
}

char			*get_number(int real_exp, unsigned long long int nbr, char *ans, int my_exp)
{
	char *s;
	char *decimal;
	char *fract;
	char *tmp;

	s = ft_strnew(1100);
	s = ft_memset(s, '0', 1100);
	s = int_to_bin(nbr, s, my_exp);
	decimal = ft_strsub(s, 0, real_exp + 1);
	fract = real_exp > size_fract(s) ? 0 :
	ft_strsub(s, real_exp + 1, size_fract(s) - real_exp);
	ans = get_int(decimal, ans);
	ans = ft_strlen(ans) == 0 || (ft_strlen(ans) == 1 && *ans == '-') ? ft_strjoin(ans, "0") : ans;
	tmp = ans;
	ans = ft_strjoin(ans, ".");
	free(tmp);
	if (fract != NULL)
		ans = get_fract(fract, ans);
	else
		ans = ft_strjoin(ans, "0");
	free(decimal);
	free(fract);
	free(s);
	return (ans);
}

int				ft_f(long double nbr, t_qual *qual)
{
	int			real_exp;
	char		*ans;
	int			size;
	t_ldbl		d1;
	int flag;

	ans = ft_strnew(310);
	d1.f = nbr;
	qual->sign = d1.b.sign;
	real_exp = d1.b.exp - 16383;
	flag = real_exp;
	real_exp = real_exp < 0 ? -1 : real_exp;
	ans = nbr < 0 ? ft_strjoin(ans, "-") : ans;
	ans = d1.b.exp != 0 ? get_number(real_exp, d1.b.man, ans, flag) :
	ft_strjoin(ans, "0.000000");
	ans = add_precision(ans, qual);
	ans = add_width(ans, qual);
	ft_putstr(ans);
	size = ft_strlen(ans);
	free(ans);
	d1.f = 0;
	return (size);
}
