/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:06:39 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 14:46:16 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_b(t_lst *b, int numb_str, t_head *head, int tmp)
{
	if (head->operation && (ft_strcmp(head->operation, "sb") == 0 ||
	ft_strcmp(head->operation, "ss") == 0) && numb_str <= 2)
		ft_printf(WHITE"%*s[%11d] "RESET WHITE, 50 - tmp, " ",
		b->value);
	else if (head->operation && (ft_strcmp(head->operation, "pb") == 0 ||
	ft_strcmp(head->operation, "rrb") == 0 ||
	ft_strcmp(head->operation, "rrr") == 0)
	&& numb_str == 1)
		ft_printf(WHITE"%*s[%11d] "RESET WHITE, 50 - tmp, " ",
		b->value);
	else if (head->operation && (ft_strcmp(head->operation, "rb") == 0 ||
	ft_strcmp(head->operation, "rr") == 0) && numb_str == get_len_stack(head->b)
	&& head->operation)
		ft_printf(WHITE"%*s[%11d] "RESET WHITE, 50 - tmp, " ",
		b->value);
	else
		ft_printf(MAGENTA"%*s[%11d] "RESET GREEN, 50 - tmp, " ",
		b->value);
	tmp = b->index;
	while (b->index-- > 0)
		ft_printf("#");
	b->index = tmp;
	ft_printf("\n"RESET);
}

int		print_a(t_lst *a, char *command, int numb_str, t_head *head)
{
	int	tmp;

	if (command && (ft_strcmp(command, "sa") == 0 ||
	ft_strcmp(command, "ss") == 0) && numb_str <= 2 && head->operation)
		ft_printf(WHITE"[%11d]  "RESET WHITE, a->value);
	else if (command && (ft_strcmp(command, "pa") == 0 ||
	ft_strcmp(command, "rra") == 0 || ft_strcmp(command, "rrr") == 0)
	&& numb_str == 1 && head->operation)
		ft_printf(WHITE"[%11d]  "RESET WHITE, a->value);
	else if (command && (ft_strcmp(command, "ra") == 0 ||
	ft_strcmp(command, "rr") == 0) && numb_str == get_len_stack(head->a)
	&& head->operation)
		ft_printf(WHITE"[%11d]  "RESET WHITE, a->value);
	else
		ft_printf(MAGENTA"[%11d]  "RESET GREEN, a->value);
	tmp = a->index;
	while (a->index-- > 0)
		ft_printf("#");
	a->index = tmp;
	return (tmp);
}

void	print_only_b(t_lst *b, char *command, int numb_str, t_head *head)
{
	int		tmp;

	if (command && (ft_strcmp(command, "sb") == 0 ||
	ft_strcmp(command, "ss") == 0) && numb_str <= 2 && head->operation)
		ft_printf(WHITE"%65s[%11d] "RESET WHITE, " ", b->value);
	else if (command && (ft_strcmp(command, "pb") == 0 ||
	ft_strcmp(command, "rrb") == 0 || ft_strcmp(command, "rrr") == 0) &&
	numb_str == 1 && head->operation)
		ft_printf(WHITE"%65s[%11d] "RESET WHITE, " ", b->value);
	else if (command && (ft_strcmp(command, "rb") == 0 ||
	ft_strcmp(command, "rr") == 0) && numb_str == get_len_stack(head->b)
	&& head->operation)
		ft_printf(WHITE"%65s[%11d] "RESET WHITE, " ", b->value);
	else
		ft_printf(MAGENTA"%65s[%11d] "RESET GREEN, " ", b->value);
	tmp = b->index;
	while (b->index-- > 0)
		ft_printf("#");
	b->index = tmp;
	ft_printf("\n"RESET);
}

void	print_only_a(t_lst *a, char *command, int numb_str, t_head *head)
{
	int		tmp;

	if (command && (ft_strcmp(command, "sa") == 0 ||
	ft_strcmp(command, "ss") == 0) && numb_str <= 2 && head->operation)
		ft_printf(WHITE"[%11d]  "RESET WHITE, a->value);
	else if (command && (ft_strcmp(command, "pa") == 0 ||
	ft_strcmp(command, "rra") == 0 || ft_strcmp(command, "rrr") == 0)
	&& numb_str == 1 && head->operation)
		ft_printf(WHITE"[%11d]  "RESET WHITE, a->value);
	else if (command && (ft_strcmp(command, "ra") == 0 ||
	ft_strcmp(command, "rr") == 0) && numb_str == get_len_stack(head->a)
	&& head->operation)
		ft_printf(WHITE"[%11d]  "RESET WHITE, a->value);
	else
		ft_printf(MAGENTA"[%11d]  "RESET GREEN, a->value);
	tmp = a->index;
	while (a->index-- > 0)
		ft_printf("#");
	a->index = tmp;
	ft_printf("\n"RESET);
}

void	print_stacks(t_head *head, char *command, int tmp)
{
	t_lst	*a;
	t_lst	*b;
	int		numb_str;

	a = head->a;
	b = head->b;
	numb_str = 1;
	tmp = command ? ft_printf(WHITE"%47s COMMAND: ["CYAN" %s "RESET WHITE"]\n"
		RESET, " ", command) : 0;
	ft_printf(RED_DARK"\t\tSTACK A%57sSTACK B\n"RESET, " ");
	while (a || b)
	{
		if (a && !b)
			print_only_a(a, command, numb_str, head);
		else if (!a && b)
			print_only_b(b, command, numb_str, head);
		else
		{
			tmp = print_a(a, command, numb_str, head);
			print_b(b, numb_str, head, tmp);
		}
		a = a ? a->next : a;
		b = b ? b->next : b;
		numb_str++;
	}
}
