/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:24:28 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/13 15:37:54 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define START 1
# define EXIT -1
# define WITH_NEG 1
# define NO_NEG 0
# define SIZE_WINDOW_X 2560
# define SIZE_WINDOW_Y 1440
# define ROOM_SIZE 50
# define ANTS_SIZE 100
# define SPEED 200
# include "libft.h"
# include <stdio.h>
# include <limits.h>
# include <SDL.h>
# include <SDL_ttf.h>

/*
** Структура, хранящая входной файл
*/
typedef struct			s_file_txt
{
	char				*text;
	struct s_file_txt	*next;
}						t_file_txt;
/*
** Структура, описывающая комнату
*/
typedef struct			s_room
{
	double				x;
	double				y;
	int					count_links;
	int					path_len;
	int					in_path :2;
	int					used;
	int					ant_id;
	char				*name;
	struct s_link		*links;
	struct s_room		*next;
}						t_room;
/*
** Структура, описывающая входные данные
*/
typedef struct			s_map
{
	int					count_ants;
	int					count_rooms;
	struct s_room		*start;
	struct s_room		*exit;
	int					prev_command;
	struct s_room		**array_rooms;
	int					has_links:2;
	int					count_out_line;
	struct s_file_txt	*input;

}						t_map;
/*
** Структура, описывающая связи определенной комнаты
*/
typedef struct			s_link
{
	struct s_room		*room_l;
	struct s_link		*next;
}						t_link;

typedef struct			s_links
{
	struct s_room		*room_start;
	struct s_room		*room_end;
	struct s_links		*next;
}						t_links;

typedef struct			s_path
{
	struct s_room		*room_path;
	struct s_path		*next;
}						t_path;

typedef struct			s_paths
{
	int					size;
	struct s_path		*path;
	struct s_paths		*next;
}						t_paths;

typedef struct			s_queue
{
	struct s_room		*room_queue;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	TTF_Font			*sans;
	SDL_Surface			*surface;
	SDL_Texture			*background;
	SDL_Texture			*ant;
	struct s_room		*rooms;
	struct s_paths		*best_paths;
	int					best_paths_count;
	struct s_links		*links;
	struct s_map		*map;
}						t_sdl;

typedef struct			s_ants
{
	double				x;
	double				y;
	double				speed_x;
	double				speed_y;
	struct s_path		*cur_path;
	struct s_ants		*next;
}						t_ants;
void					sort_array_by_name(t_map **map, int size);
void					list_to_array(t_map *map, t_room *rooms,
										int count_rooms);
void					count_ants(char *line, t_map *map);
void					parse_comment(char *str, t_map *map);
void					error(char *str);
void					parse_rooms(char *str, t_map *map, t_room **rooms);
int						check_digits(char *str, int with_neg);
int						check_intmax(char *str);
t_room					*init_room(char *name, int x, int y);
void					parse_links(char **str, t_map *map);
void					reverse_input_file(t_file_txt **lst);
void					add_to_file_txt(t_file_txt **input, char *line);
void					free_rooms(t_room *rooms);
void					free_map(t_map *map);
t_file_txt				*init_input_file(char *text);
void					bfs(t_map *map);
t_paths					*get_all_paths(t_map *map, t_room *rooms, int status);
void					reverse_paths(t_paths **paths);
t_map					*init(void);
t_file_txt				*init_input_file(char *text);
t_room					*init_room(char *name, int x, int y);
void					print_out(t_file_txt *input, t_paths *paths,
									int count_ants, int count_lines);
void					path_removal(t_paths *paths, int count_path);
void					free_paths(t_paths *paths);
void					ft_swap(int *a, int *b);
int						choose_path(int ants, t_paths *paths, t_map *map);
t_room					*find_room(char *name, t_room **array, int left,
									int right);
void					clear_full(t_room *room);
void					delete_link(t_room **room_path, t_room *next_room);
void					create_link(t_room *room, t_room *link);
void					print_paths(t_paths *paths);
void					clear_bfs(t_room *room);
void					free_input(t_file_txt *input);
/*
** SDL
*/
void					highlight_paths(t_sdl *sdl, t_paths *paths, int path);
void					parse_link_and_add(char *line, t_map *map,
												t_links **links);
void					draw_links(t_sdl *sdl, t_links *links);
void					draw_rooms(t_sdl *sdl, t_room *rooms, t_map *map);
t_sdl					*create_window(void);
void					put_text(t_sdl *sdl, char *message, SDL_Color color,
						t_room *cur_room);
void					pressed(int key);
void					print_out_sdl(t_sdl *sdl, t_map *map, t_paths *paths,
t_ants					*init_ants(t_path *cur_path);
						int count_lines);
t_links					*init_links(t_room *room_start, t_room *room_end);
void					redraw(t_sdl *sdl, t_ants *ants);
#endif
