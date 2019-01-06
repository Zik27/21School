/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:10:01 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/05 19:56:31 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFF_SIZE 21

typedef struct	s_tetriminos_figure
{
	struct s_tetriminos_figure	*next;
	int							*data;
}				t_tetriminos_fig;
int				check_valid(char *file, t_tetriminos_fig **head);
int				prepare_data(char *square, t_tetriminos_fig **head);
int				lst_push_back(t_tetriminos_fig **begin_list, int *data);
void			free_lst(t_tetriminos_fig **head);
char			**build_map(int side);
void			free_map(char **map, int count);
int				print_map(char **map, int size);
int				get_height(int *data);
int				get_left_width(int *data);
int				get_right_width(int *data);
int				place(int *data, char **map, int x, int y);
void			clear_map(char **map, int *data, int error_index, int *coords);
#endif
