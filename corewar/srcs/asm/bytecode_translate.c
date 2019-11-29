/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_translate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:12:20 by aestella          #+#    #+#             */
/*   Updated: 2019/11/29 13:22:43 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	args_to_bcode(t_tokens **args, unsigned char **bytes, int code_op)
{
	int	i;
	int arg_int;

	i = -1;
	while (args[++i])
	{
		arg_int = args[i]->data_int;
		if (args[i]->type == T_REG)
		{
			int32_to_bytecode((*bytes), arg_int, 1);
			(*bytes)++;
		}
		else if (args[i]->type == T_IND || args[i]->type == INDIRECT_LABEL)
		{
			int32_to_bytecode((*bytes), arg_int, 2);
			*bytes += 2;
		}
		else if (args[i]->type == T_DIR || args[i]->type == DIRECT_LABEL)
		{
			int32_to_bytecode(*bytes, arg_int, g_instr[code_op - 1].t_dir_size);
			*bytes += g_instr[code_op - 1].t_dir_size;
		}
		else
			error("Invalid type of argument");
	}
}

void	translate_to_bytecode_ins(t_instr *instr, unsigned char **bytes)
{
	while (instr)
	{
		int32_to_bytecode(*bytes, instr->code_op, 1);
		(*bytes)++;
		if (g_instr[instr->code_op - 1].args_types_code)
		{
			int32_to_bytecode(*bytes, get_code_types(instr->args), 1);
			(*bytes)++;
			args_to_bcode(instr->args, bytes, instr->code_op);
		}
		else
			args_to_bcode(instr->args, bytes, instr->code_op);
		instr = instr->next;
	}
}

void	translate_to_bytecode(t_player *player, int new_fd)
{
	int				len;
	unsigned char	*bytes;
	unsigned char	*begin;

	len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 +
				player->sum_size_exec_code;
	if (!(bytes = (unsigned char *)malloc((len + 1) * sizeof(unsigned char))))
		error("Failed to initialize byte array");
	ft_bzero(bytes, len);
	begin = bytes;
	int32_to_bytecode(bytes, COREWAR_EXEC_MAGIC, 4);
	bytes += 4;
	ft_memcpy(bytes, player->name, ft_strlen(player->name));
	bytes += PROG_NAME_LENGTH;
	int32_to_bytecode(bytes, 0, 4);
	bytes += 4;
	int32_to_bytecode(bytes, player->sum_size_exec_code, 4);
	bytes += 4;
	ft_memcpy(bytes, player->comment, ft_strlen(player->comment));
	bytes += COMMENT_LENGTH;
	int32_to_bytecode(bytes, 0, 4);
	bytes += 4;
	translate_to_bytecode_ins(player->instr, &bytes);
	write(new_fd, begin, len);
	free(begin);
}
