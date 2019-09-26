/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:35:39 by djast             #+#    #+#             */
/*   Updated: 2019/09/26 16:18:20 by djast            ###   ########.fr       */
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
	int					size_jump;
	int					registers[REG_NUMBER];
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_vm_info
{
	int					count_players;
	int					cycles_to_die;
	int					cycle;
	t_carriage			*carriages;
	char				*map;
}						t_vm_info;

typedef struct			s_champ
{
	int					id;
	char				*name;
	char				*comment;
	int					code_size;
	char				*code;
	struct s_champ		*next;
}						t_champ;

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
#endif