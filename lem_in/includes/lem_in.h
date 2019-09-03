/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:24:28 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/03 12:43:03 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define START 1
# define EXIT -1
# define WITH_NEG 1
# define NO_NEG 0
# include "libft.h"
# include <stdio.h>

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
/* Структура, описывающая входные данные */
typedef struct			s_map
{
	int					count_ants;
	int					count_rooms;
	struct s_room		*start;
	struct s_room		*exit;
	int					prev_command;
	struct s_room		**array_rooms;
	int					has_links:2;
}						t_map;
/* Структура, описывающая связи определенной комнаты */
typedef struct			s_link
{
	struct s_room		*room_l;
	struct s_link		*next;
}						t_link;
/*Структура, хранящая входной файл */
typedef struct			s_file_txt
{
	char				*text;
	struct	s_file_txt	*next;
}						t_file_txt;

void	sort_array_by_name(t_map **map, int size);
void	list_to_array(t_map *map, t_room *rooms, int count_rooms);
void	count_ants(char *line, t_map *map);
void	parse_comment(char *str, t_map *map);
void	error(char *str);
void	parse_rooms(char *str, t_map *map, t_room **rooms);
int		check_digits(char *str, int with_neg);
int		check_intmax(char *str);
t_room	*init_room(char *name, int x, int y);
void	parse_links(char **str, t_map *map);

#endif