/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:29:08 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/26 17:50:23 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include "asm_operations.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define OFFSET_CMD_NAME 5
# define OFFSET_CMD_COMMENT 8
# define QUOTE 1

typedef struct				s_tokens
{
	char			*data;
	unsigned short	size;
	struct s_tokens	*next;
}							t_tokens;

typedef struct				s_instructions
{
	char					*label;
	unsigned short			code_op;
	struct s_tokens			*tokens;
	int						sum_size_exec_code;
	struct s_instructions	*next;
}							t_instructions;

typedef struct		s_player
{
	char					*name;
	char					*comment;
	int						num_row;
	int						num_col;
	struct s_instructions	*instr;
}					t_player;

void	error(char *str);
void	error_file(char *str, int col, int row);
char	*ft_strndup(const char *src, int i);
int		is_comment(char *line, t_player *player);

#endif
