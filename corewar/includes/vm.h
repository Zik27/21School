/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:35:39 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 15:23:52 by djast            ###   ########.fr       */
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

typedef struct		s_champ
{
	int				id;
	char			*name;
	char			*comment;
	int				code_size;
	char			*code;
	struct s_champ	*next;
}					t_champ;

void			cerror(char *message, char *error_file);
void			print_help(char **argv);
void			parse_args(int argc, char **argv);
t_champ			*check_file(char *arg, int id);
t_champ			*init_charp(int id);
char 			*get_champ_name(int fd);
int				get_champ_code_size(int fd);
char			*get_champ_comment(int fd);
char			*get_champ_code(int fd, int code_size);
#endif