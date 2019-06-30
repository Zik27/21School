/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:06:05 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/30 18:22:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

typedef struct	s_lst
{
	struct s_lst	*next;
	int				value;
	
}				t_lst;
typedef struct	s_head
{
	struct	s_lst	*a;
	struct	s_lst	*b;
}				t_head;
int	valid(char **str);
t_lst	*create_lst(char **data);
t_head	*create_head(char **data);
int	read_command(t_head **head);
void	do_sa(t_head **head);
void	do_sb(t_head **head);
void	do_ss(t_head **head);
void	do_pa(t_head **head);
void	do_pb(t_head **head);
t_lst	*ft_create_elem(int data);

#endif