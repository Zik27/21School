/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:24:28 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/23 13:46:51 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define WITH_NEG 1
# define NO_NEG 0
# include "libft/libft.h"

/* Структура, описывающая входные данные */
typedef struct			s_map
{
	int					count_ants;
	int					has_start;
	int					has_exit;
	int					prev_step;
}						t_map;
/* Структура, описывающая комнату */
typedef struct			s_room
{
	int					x;
	int					y;
	int					count_links;
	char				*name;
	struct s_link		*links;
	struct s_room		*next;
}						t_room;
/* Структура, описывающая связи определенной комнаты */
typedef struct			s_link
{
	char				*name;
	struct s_link		*next;
}						t_link;

void	count_ants(char *line, t_map *map);
void	parse_comment(char *str, t_map *map);
void	error(char *str);
void	parse_rooms(char *str, t_map *map, t_room *rooms);
int		check_digits(char *str, int with_neg);
int		check_intmax(char *str);
t_room	*init_room(char *name, int x, int y);
void	parse_links(char *str, t_map *map, t_room *rooms);

#endif