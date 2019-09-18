/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:29:08 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/18 16:54:02 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	//struct s_commands	*commands;
}					t_player;

#endif
