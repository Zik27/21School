/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dasm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:17:17 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/02 17:24:47 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int		bytecode_to_int(unsigned char *buf, int count_bytes)
{
	int result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = buf[0] & 0b10000000;
	while (count_bytes)
	{
		if (sign)
			result += (buf[count_bytes - 1] ^ 0xFF) << (i++ * 8); // инвертирование
		else
			result += buf[count_bytes - 1] << (i++ * 8);
		count_bytes--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

int		count_args(unsigned char types)
{
	unsigned char	tmp;

	if (!(tmp = 0b11000000 & types))
		return (0);
	else if (!(tmp = 0b00110000 & types))
		return (1);
	else if (!(tmp = 0b00001100 & types))
		return (2);
	else if (!(tmp = 0b00000011 & types))
		return (3);
	else
		return (-1);
}

int		get_exec_size(int fd)
{
	int				ret;
	unsigned char	buf[4];

	ret = read(fd, buf, 4);
	if (ret < 4)
		error("Invalid file: error reading size execution code");
	return (bytecode_to_int(buf, 4));
}

void	add_ins_dasm(t_dasm *dasm, t_inst_dasm *instr)
{
	t_inst_dasm *tmp;

	tmp = dasm->instr;
	if (!tmp)
		dasm->instr = instr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = instr;
	}
}

void	add_arg_to_instr(t_inst_dasm *ins, t_args_dasm *argument)
{
	t_args_dasm	*tmp;

	while (ins->next)
		ins = ins->next;
	if (!ins->args)
		ins->args = argument;
	else
	{
		tmp = ins->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = argument;
	}
}