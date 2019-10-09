/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:35:39 by djast             #+#    #+#             */
/*   Updated: 2019/10/08 18:28:55 by djast            ###   ########.fr       */
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
	int					args_types[3];
	int					args[3];
	struct s_carriage	*next;
}						t_carriage;

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

typedef struct			s_vm_info
{
	int					count_players;
	int					cycles_to_die;
	int					cycle;
	int					live;
	t_carriage			*carriages;
	t_champ				*last_live_player;
	char				*map;
}						t_vm_info;



void			cerror(char *message, char *error_file);
void			print_help(char **argv);
t_champ			*parse_args(int argc, char **argv);
t_champ			*check_file(char *arg, int id);
t_champ			*init_champ(int id);
char 			*get_champ_name(int fd);
int				get_champ_code_size(int fd);
char			*get_champ_comment(int fd);
char			*get_champ_code(int fd, int code_size);
int				get_player_count(t_champ *champs);
t_vm_info		*init_vm_info(t_champ *players);
void			place_players_on_arena(t_champ *champs, t_vm_info *info);
void			print_map(char *map);
t_carriage		*init_carriages(t_champ *champs, t_vm_info *info);
t_carriage		*init_carriage(int id, t_champ *cur_player, t_vm_info *info);
void			print_carriages(t_carriage *car);
t_champ			*find_player_by_id(t_champ *champs, int id);
void			introducing(t_champ	*champs, t_vm_info *info);
t_champ			*find_player_by_id(t_champ *champs, int id);
void			set_op_steps(t_carriage *carr);
int				bytecode_to_int(unsigned char *buf, int count_bytes);
void			rewrite(t_vm_info *info, int addr, int number);

void			make_command_live(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_ld(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_st(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_add(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_sub(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_and(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_or(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_xor(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_zjmp(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_ldi(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_sti(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_fork(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_lld(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_lldi(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_lfork(t_vm_info *info, t_champ *champs, t_carriage *carr);
void			make_command_aff(t_vm_info *info, t_champ *champs, t_carriage *carr);

#endif