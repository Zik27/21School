/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:10:01 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/04 18:35:29 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFF_SIZE 21

typedef struct	tetriminos_figure
{
	struct tetriminos_figure	*next;
	int							*data;
}				tetriminos_fig;

int		check_valid(char *file, tetriminos_fig **head);
int		prepare_data(char *square, tetriminos_fig **head);
int		lst_push_back(tetriminos_fig **begin_list, int *data);
void	free_lst(tetriminos_fig **head);
char	**build_map(int side);
void	free_map(char **map, int count);

#endif 
