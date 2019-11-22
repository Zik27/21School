/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:35:39 by djast             #+#    #+#             */
/*   Updated: 2019/11/22 16:14:24 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include "asm_operations.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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

typedef struct 			s_carriage
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
	t_carriage			*carriages;
	t_champ				*last_live_player;
	char				*map;
}						t_vm_info;



void			cerror(char *message, char *error_file);
void			print_help(char **argv);
t_champ			*parse_args(int argc, char **argv, t_vm_info *info);
t_champ			*check_file(char *arg, int id);
t_champ			*init_champ(int id);
char 			*get_champ_name(int fd);
int				get_champ_code_size(int fd);
char			*get_champ_comment(int fd);
char			*get_champ_code(int fd, int code_size);
int				get_player_count(t_champ *champs);
t_vm_info		*init_vm_info(t_vm_info **info, t_champ *players);
void			place_players_on_arena(t_champ *champs, t_vm_info *info);
void			print_map(char *map);
t_carriage		*init_carriages(t_champ *champs, t_vm_info *info);
t_carriage		*init_carriage(t_champ *cur_player, t_vm_info *info);
void			print_carriages(t_carriage *car);
t_champ			*find_player_by_id(t_champ *champs, int id);
void			introducing(t_champ	*champs, t_vm_info *info);
t_champ			*find_player_by_id(t_champ *champs, int id);
void			set_op_steps(t_carriage *carr);
int				bytecode_to_int(t_vm_info *info, t_carriage *carr, int pos, int count_bytes);
void			rewrite(t_vm_info *info, int addr, int number);
void			get_op_arg_type(t_vm_info *info, t_carriage *carr);
void			get_op_arg(t_vm_info *info, t_carriage *carr, int cmd);
void			calc_jump_size(t_carriage *carr);
char			*int_to_bytecode(int value, int size);
void			create_carr_copy(t_vm_info *info, t_carriage *carr);
int				check_cycle_to_die(t_vm_info *info);
void			delete_death_carr(t_vm_info *info, t_carriage *carr);
void			free_all(t_vm_info *info, t_champ *champs);

void			make_command_live(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_ld(t_vm_info *info, t_carriage *carr);
void			make_command_st(t_vm_info *info, t_carriage *carr);
void			make_command_add(t_vm_info *info, t_carriage *carr);
void			make_command_sub(t_vm_info *info, t_carriage *carr);
void			make_command_and(t_vm_info *info, t_carriage *carr);
void			make_command_or(t_vm_info *info, t_carriage *carr);
void			make_command_xor(t_vm_info *info, t_carriage *carr);
void			make_command_zjmp(t_vm_info *info, t_carriage *carr);
void			make_command_ldi(t_vm_info *info, t_carriage *carr);
void			make_command_sti(t_vm_info *info, t_carriage *carr);
void			make_command_fork(t_vm_info *info, t_carriage *carr);
void			make_command_lld(t_vm_info *info, t_carriage *carr);
void			make_command_lldi(t_vm_info *info, t_carriage *carr);
void			make_command_lfork(t_vm_info *info, t_carriage *carr);
void			make_command_aff(t_vm_info *info, t_carriage *carr);

#endif