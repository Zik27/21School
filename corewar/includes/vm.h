/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:35:39 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 15:41:10 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# define CODE_D 1
# define CODE_DUMP 2
# include <SDL.h>
# include <SDL_ttf.h>
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include "asm_operations.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define SIZE_WIN_X 1700
# define SIZE_WIN_Y 1300
# define SYMBOL_SIZE 18
# define SPACE_SIZE 2
# define COREWAR_TEXT_X SIZE_WIN_X * 0.77
# define COREWAR_TEXT_Y SIZE_WIN_Y * 0.07
# define COREWAR_TEXT_SIZE_X SIZE_WIN_X * 0.22
# define COREWAR_TEXT_SIZE_Y 100
# define SPEED_TEXT_X SIZE_WIN_X * 0.77
# define SPEED_TEXT_Y SIZE_WIN_Y * 0.2
# define SPEED_TEXT_SIZE_X SIZE_WIN_X * 0.05
# define SPEED_TEXT_SIZE_Y 40
# define SPEED_RES_X SIZE_WIN_X * 0.83
# define SPEED_RES_Y SIZE_WIN_Y * 0.2
# define SPEED_RES_SIZE_X SIZE_WIN_X * 0.05
# define SPEED_RES_SIZE_Y 40
# define CYCLE_TEXT_X SIZE_WIN_X * 0.77
# define CYCLE_TEXT_Y SIZE_WIN_Y * 0.25
# define CYCLE_TEXT_SIZE_X SIZE_WIN_X * 0.05
# define CYCLE_TEXT_SIZE_Y 40
# define CYCLE_RES_X SIZE_WIN_X * 0.83
# define CYCLE_RES_Y SIZE_WIN_Y * 0.25
# define CYCLE_RES_SIZE_X SIZE_WIN_X * 0.05
# define CYCLE_RES_SIZE_Y 40

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Event			window_event;
	TTF_Font			*font;
	SDL_Texture			*text;
	SDL_Surface			*surface;
	int					speed;
	int					is_pause;
}						t_sdl;

typedef struct			s_champ
{
	int					id;
	char				*name;
	char				*comment;
	int					code_size;
	char				*code;
	int					count_lives;
	int					last_live;
	struct s_champ		*next;
}						t_champ;

typedef struct			s_carriage
{
	int					id;
	int					carry;
	int					op_code;
	int					cycle_last_live;
	int					op_steps;
	int					cur_pos;
	int					cur_step;
	int					jump_size;
	int					registers[REG_NUMBER];
	t_champ				*champ;
	int					*args_types;
	int					*args;
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_vm_info
{
	int					count_players;
	int					cycles_to_die;
	int					cycles_after_check;
	int					checks;
	int					cycle;
	int					live;
	int					dump_cycle;
	int					dump_type;
	int					debug_flag;
	t_carriage			*carriages;
	t_champ				*last_live_player;
	char				*map;
	int					*color_map;
	t_champ				*cur_champ;
	t_champ				*champs;
	t_sdl				*sdl;
}						t_vm_info;

void					cerror(char *message, char *error_file);
void					print_help(char **argv);
t_champ					*parse_args(int argc, char **argv,
														t_vm_info *info);
t_champ					*check_file(char *arg, int id);
t_champ					*init_champ(int id);
char					*get_champ_name(int fd);
int						get_champ_code_size(int fd);
char					*get_champ_comment(int fd);
char					*get_champ_code(int fd, int code_size);
int						get_player_count(t_champ *champs);
t_vm_info				*init_vm_info(t_vm_info **info, t_champ *players);
void					place_players_on_arena(t_champ *champs,
												t_vm_info *info);
void					print_map(char *map, int count_in_row);
t_carriage				*init_carriages(t_champ *champs, t_vm_info *info);
t_carriage				*init_carriage(t_champ *cur_player, t_vm_info *info);
void					print_carriages(t_carriage *car);
t_champ					*find_player_by_id(t_champ *champs, int id);
void					introducing(t_champ	*champs, t_vm_info *info);
void					set_op_steps(t_carriage *carr);
int						bytecode_to_int(t_vm_info *info, int pos,
											int count_bytes);
void					rewrite(t_vm_info *info, int addr, int number,
									t_champ *champ);
void					get_op_arg_type(t_vm_info *info, t_carriage *carr);
void					get_op_arg(t_vm_info *info, t_carriage *carr, int cmd);
void					calc_jump_size(t_carriage *carr);
char					*int_to_bytecode(int value, int size);
void					create_carr_copy(t_vm_info *info, t_carriage *carr);
int						check_cycle_to_die(t_vm_info *info);
void					delete_death_carr(t_vm_info *info, t_carriage *carr);
void					free_all(t_sdl *sdl, t_vm_info *info, t_champ *champs);
void					free_champions(t_champ *champs);
char					*hex_to_charhex(int value);
t_sdl					*init_sdl();
void					draw(t_sdl *sdl, t_vm_info *info);
void					draw_map(t_sdl *sdl, t_vm_info *info);
void					draw_map_symbol(t_sdl *sdl, char text, SDL_Rect r,
											SDL_Color color);
void					draw_right_panel(t_sdl *sdl, t_vm_info *info);
void					draw_text_on_right_panel(t_sdl *sdl, t_vm_info *info);
SDL_Color				*create_sdl_color(int r, int g, int b, int a);
SDL_Rect				*create_sdl_rect(int x, int y, int w, int h);
void					draw_text(t_sdl *sdl, char *text, SDL_Rect button,
										SDL_Color color);
void					parse_champion(t_champ **champs, t_champ **cur_champ,
								char *filename, int i);
int						is_flag(char *place, char *name, int max_players,
															t_champ *champs);
void					parse_dump_flag(char *command, char *argv_cycle,
															t_vm_info *info);
void					set_champion_id(t_champ *champs);
int						get_argv_cor(char **argv);
void					sdl_loop(t_champ *champs, t_vm_info *info, t_sdl *sdl,
																int *i);
int						make_step_cycle(t_vm_info *info, t_champ *champs);
void					make_command(t_vm_info *info, t_champ *champs,
														t_carriage *carr);
int						get_info_for_command(t_vm_info *info, t_carriage *carr);
void					skip_command(t_carriage *carr, int args[3]);
int						check_command_args(t_carriage *carr, int args[3]);
int						check_registers(t_vm_info *info, t_carriage *carr);
void					make_command_live(t_vm_info *info, t_champ *champs,
											t_carriage *carr);
void					make_command_ld(t_vm_info *info, t_carriage *carr);
void					make_command_st(t_vm_info *info, t_carriage *carr);
void					make_command_add(t_vm_info *info, t_carriage *carr);
void					make_command_sub(t_vm_info *info, t_carriage *carr);
void					make_command_and(t_vm_info *info, t_carriage *carr);
void					make_command_or(t_vm_info *info, t_carriage *carr);
void					make_command_xor(t_vm_info *info, t_carriage *carr);
void					make_command_zjmp(t_vm_info *info, t_carriage *carr);
void					make_command_ldi(t_vm_info *info, t_carriage *carr);
void					make_command_sti(t_vm_info *info, t_carriage *carr);
void					make_command_fork(t_vm_info *info, t_carriage *carr);
void					make_command_lld(t_vm_info *info, t_carriage *carr);
void					make_command_lldi(t_vm_info *info, t_carriage *carr);
void					make_command_lfork(t_vm_info *info, t_carriage *carr);
void					make_command_aff(t_vm_info *info, t_carriage *carr);

#endif
