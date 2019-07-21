/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:06:05 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/21 19:02:37 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

typedef struct	s_lst
{
	struct s_lst	*next;
	int				value;
	int				mark:2;
	
}				t_lst;
typedef struct	s_head
{
	struct	s_lst	*a;
	struct	s_lst	*b;
	int				do_write:2;
}				t_head;
int			valid(char **str);
t_lst		*create_lst(char **data);
t_head		*create_head(char **data, int write);
int			read_command(t_head **head);
void		do_sa(t_head **head);
void		do_sb(t_head **head);
void		do_ss(t_head **head);
void		do_pa(t_head **head);
void		do_pb(t_head **head);
t_lst		*ft_create_elem(int data, int mark);
void		delete_last_elem(t_lst **list);
void		do_ra(t_head **head);
void		do_rb(t_head **head);
void		do_rr(t_head **head);
void		do_rra(t_head **head);
void		do_rrb(t_head **head);
void		do_rrr(t_head **head);
int			check_sort(t_head *head);
int			get_len_stack(t_lst *stack);
void		sorting_below_four(t_head **head, int length);
void		sorting_below_six(t_head **head, int length);
int			get_smallest(t_lst *stack);
void		case_for_five(t_head **head);
int			get_max(t_lst *stack);
void		sorting_more_six(t_head **head);
void		swap_value(int *a, int *b);
void		main_sorting(t_head **head);

#endif