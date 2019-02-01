/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:32:21 by djast             #+#    #+#             */
/*   Updated: 2019/02/01 14:27:18 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include "Libft/libft.h"

# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define BLACK		"\033[30;1m"
# define RED		"\033[31;1m"
# define GREEN		"\033[32;1m"
# define YELLOW		"\033[33;1m"
# define BLUE		"\033[34;1m"
# define MAGENTA	"\033[35;1m"
# define CYAN		"\033[36;1m"
# define WHITE		"\033[37;1m"

/*
** Структура, описывающие поведение спецификатора.
** minus - {Флаги} "-" - выводимое значение выравнивается по левому краю в пределах минимальной ширины поля.
** plus - {Флаги} "+" - всегда указывать знак (плюс или минус) для выводимого десятичного числового значения.
** space - {Флаги} " " - помещать перед результатом пробел, если первый символ значения не знак.
** hash - {Флаги} "#" - «альтернативная форма» вывода значения (Для 2, 8, 16-ричных СС).
** zero - {Флаги} "0" - дополнять поле до ширины, указанной в поле ширина управляющей последовательности, символом 0.
**-------------------------------------------------------------------------------------------------------------------
** width - {Ширина} - указывает минимальную ширину поля (включая знак для чисел).
**-------------------------------------------------------------------------------------------------------------------
** precision - {Точность} - минимальное количество символов, которое должно появиться при обработке типов d, i, o, u, x, X;
** precision - {Точность} - минимальное количество символов, которое должно появиться после точки при обработке типов a, A, e, E, f, F;
** precision - {Точность} - максимальное количество значащих символов для типов g и G;
** precision - {Точность} - максимальное число символов, которые будут выведены для типа s;
**-------------------------------------------------------------------------------------------------------------------
** lenght - {Размер} "l, ll, h, hh, L" - long, long long, short, char, long для float
**-------------------------------------------------------------------------------------------------------------------
** sign - знак, если это число (0 - положительное, 1 - отрицательное).
*/

typedef struct	s_qual
{
	int minus : 2;
	int plus : 2;
	int space : 2;
	int hash : 2;
	int zero : 2;
	int width;
	int precision;
	char *lenght;
	int sign : 2;
	int unsint : 2;
}				t_qual;

void			ft_putllnbr(uintmax_t n);
char		    *ft_translation(uintmax_t value, int base);
void			ft_upper_str(char *str);
unsigned int	ft_num_size(uintmax_t n);
char			*ft_check_lenght(char *str, t_qual **qual);
char			*ft_check_flags(char *str, t_qual **qual);
char			*ft_check_width(char *str, t_qual **qual, va_list *args);
char			*ft_check_precision(char *str, t_qual **qual, va_list *args);
int				ft_d(intmax_t nbr, t_qual *qual);
int				ft_f(long double d, t_qual *qual);
int				ft_x(intmax_t numb, int flag, t_qual *qual);
int				ft_o(intmax_t numb, t_qual *qual);
int				ft_p(long long addr, t_qual *qual);
int				ft_s(char *str, t_qual *qual);
int				ft_c(char str, t_qual *qual);
int				ft_u(uintmax_t d, t_qual *qual);
int				ft_percent(char percent, t_qual *qual);
void			ft_print_width(t_qual *qual, int size_nbr);
void			ft_print_presicion(t_qual *qual, int size_nbr);
intmax_t		ft_max(int count, ...);
intmax_t		ft_size_by_lenght(intmax_t nbr, t_qual *qual);
int				ft_b(intmax_t numb, t_qual *qual);
#endif