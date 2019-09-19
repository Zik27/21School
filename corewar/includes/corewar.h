/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:29:08 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/19 18:20:51 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define OFFSET_CMD_NAME 5
# define OFFSET_CMD_COMMENT 8
# define QUOTE 1

// typedef struct		s_commands
// {
// 	char				*label;
// 	char				*instruction;
// 	char				*reg;
// 	char				*direct_label;
// 	char				*direct;
// 	struct s_commands	*next;
// }					t_commands;

typedef struct		s_player
{
	char				*name;
	char				*comment;
	int					num_row;
	int					num_col;
	//struct s_commands	*commands;
}					t_player;

void	error(char *str);
void	error_file(char *str, int col, int row);
char	*ft_strndup(const char *src, int i);
int		is_comment(char *line, t_player *player);

#endif
