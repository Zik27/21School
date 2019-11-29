/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:11:48 by aestella          #+#    #+#             */
/*   Updated: 2019/11/29 13:20:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		create_file_bytecode(t_player *player)
{
	char	*new_name;
	char	*tmp;
	int		fd;

	new_name = ft_strstr(player->file_name, ".s");
	tmp = ft_strsub(player->file_name, 0, new_name - player->file_name);
	new_name = ft_strjoin(tmp, ".cor");
	fd = open(new_name, O_WRONLY);
	if (fd == -1)
	{
		open(new_name, O_CREAT);
		fd = open(new_name, O_WRONLY);
	}
	player->file_name = new_name;
	free(tmp);
	return (fd);
}

void	int32_to_bytecode(unsigned char *bytes, int value, int size)
{
	int	i;

	i = 0;
	while (size)
	{
		bytes[size - 1] = (value >> i) & 0xFF;
		i += 8;
		size--;
	}
}

int		get_code_types(t_tokens **args)
{
	int				i;
	unsigned char	result;
	int				offset;

	offset = 64;
	result = 0;
	i = 0;
	while (args[i])
	{
		if (args[i]->type == DIRECT_LABEL)
			args[i]->type = T_DIR;
		else if (args[i]->type == INDIRECT_LABEL)
			args[i]->type = T_IND;
		if (args[i]->type == INDIRECT)
			result += offset * (args[i]->type - 1);
		else
			result += offset * args[i]->type;
		offset /= 4;
		i++;
	}
	return (result);
}

void	calculate_size_exec_code(t_player *player)
{
	t_instr	*instr;
	int		size;

	size = 0;
	instr = player->instr;
	while (instr)
	{
		size += instr->size_exec_code;
		instr = instr->next;
	}
	player->sum_size_exec_code = size;
}

int		calculate_size(t_instr *instr)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (i < g_instr[instr->code_op - 1].args_num)
	{
		size += (int)instr->args[i]->size;
		i++;
	}
	size += (1 + g_instr[instr->code_op - 1].args_types_code);
	return (size);
}
