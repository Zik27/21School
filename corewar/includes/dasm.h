/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:26:22 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/09 13:43:52 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include "asm_operations.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct				s_args_dasm
{
	char				*data;
	unsigned short		size;
	struct s_args_dasm	*next;
}							t_args_dasm;

typedef struct				s_inst_dasm
{
	char					*name;
	struct s_args_dasm		*args;
	struct s_inst_dasm		*next;
}							t_inst_dasm;

typedef struct				s_dasm
{
	char					*full_name_file;
	char					*name;
	char					*comment;
	int						size;
	unsigned char			*arg_types;
	struct s_inst_dasm		*instr;
}							t_dasm;

void	error(char *str);
int		check_magic_header(int fd);
t_dasm	*init_dasm(char	*full_name);
t_inst_dasm	*init_ins_dasm(char *name);
t_args_dasm	*init_arg(char *name);
char	*get_name(int fd);
void	check_null(int fd, int bytes);
int		get_exec_size(int fd);
char	*get_comment(int fd);
void	handling_command(int fd, t_dasm *dasm);
int		create_new_fd(t_dasm *dasm);
void	write_name_comment(t_dasm *dasm, int fd);
void	write_commands(t_dasm *dasm, int new_fd);
int		bytecode_to_int(unsigned char *buf, int count_bytes);
void	add_arg_to_instr(t_inst_dasm *ins, t_args_dasm *argument);
void	add_ins_dasm(t_dasm *dasm, t_inst_dasm *instr);
void	handle_args(int fd, t_dasm *dasm, int code_op);
void	get_types(t_dasm *dasm, unsigned char types);
int		count_args(unsigned char types);
void	free_dasm(t_dasm *dasm);

#endif
