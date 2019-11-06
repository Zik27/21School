/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:14:46 by vurrigon          #+#    #+#             */
/*   Updated: 2019/11/06 15:28:07 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static void	handle_registry(int fd, t_dasm *dasm)
{
	int				ret;
	unsigned char	buf[1];
	char			*arg;
	char			*tmp;

	ret = read(fd, buf, 1);
	if (ret < 1)
		error("Invalid file: error reading number of registry");
	if (buf[0] > 99)
		error("Invalid number of registry");
	tmp = ft_itoa((int)buf[0]);
	arg = ft_strjoin("r", tmp);
	free(tmp);
	add_arg_to_instr(dasm->instr, init_arg(arg));
}

static void	handle_dir(int fd, t_dasm *dasm, int code_op)
{
	int				ret;
	unsigned char	buf[g_instr[code_op - 1].t_dir_size];
	int				res;
	char			*tmp;
	char			*arg;

	ret = read(fd, buf, g_instr[code_op - 1].t_dir_size);
	if (ret < g_instr[code_op - 1].t_dir_size)
		error("Invalid file: error reading T_DIR argument");
	dasm->size -= g_instr[code_op - 1].t_dir_size;
	res = bytecode_to_int(buf, g_instr[code_op - 1].t_dir_size);
	tmp = ft_itoa(res);
	arg = ft_strjoin("%", tmp);
	free(tmp);
	add_arg_to_instr(dasm->instr, init_arg(arg));
}

static void	handle_ind(int fd, t_dasm *dasm)
{
	int				ret;
	unsigned char	buf[2];
	char			*arg;

	ret = read(fd, buf, 2);
	if (ret < 1)
		error("Invalid file: error reading T_INDIR argument");
	dasm->size -= 2;
	arg = ft_itoa(bytecode_to_int(buf, 2));
	add_arg_to_instr(dasm->instr, init_arg(arg));
}

void	handle_args(int fd, t_dasm *dasm, int code_op)
{
	int i;

	i = 0;
	if (dasm->arg_types)
	{
		while (dasm->arg_types && dasm->arg_types[i])
		{
			if (dasm->arg_types[i] == T_REG)
			{
				handle_registry(fd, dasm);
				dasm->size--;
			}
			else if (dasm->arg_types[i] == T_DIR)
				handle_dir(fd, dasm, code_op);
			else if (dasm->arg_types[i] == T_IND - 1)
				handle_ind(fd, dasm);
			else
				error("Invalid type of argument");
			i++;
		}
	}
	else
		handle_dir(fd, dasm, code_op);
}