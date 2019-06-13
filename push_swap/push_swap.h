/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:06:05 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/13 18:16:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

typedef struct	s_lst
{
	int				value;
	struct s_list	*next;
}				t_lst;
typedef struct	s_head
{
	struct s_list	*a;
	struct s_list	*b;
}				t_head;
int	valid(char **str, int count);
t_head	*create_head(char **nbrs);
#endif