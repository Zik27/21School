/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:15:44 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/01 11:28:05 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static int	read_instr(int fd, t_dasm *dasm)
{
	int				ret;
	unsigned char	buf[1];

	ret = read(fd, buf, 1);
	if (buf[0] > 16)
		error("Invalid instruction code");
	if (ret < 1)
		error("Invalid file: error reading instruction code");
	add_ins_dasm(dasm, init_ins_dasm(g_instr[buf[0] - 1].name));
	return (buf[0]);
}

static void	read_arg_types_code(int fd, t_dasm *dasm)
{
	int				ret;
	unsigned char	buf[1];

	ret = read(fd, buf, 1);
	if (ret < 1)
		error("Invalid file: error reading types code");
	get_types(dasm, buf[0]);
}

void	handling_command(int fd, t_dasm *dasm)
{
	int	code_op;
	char	*buf[1];
	int		ret;

	while (dasm->size)
	{
		code_op = read_instr(fd, dasm);
		dasm->size--;
		if (g_instr[code_op - 1].args_types_code)
		{
			read_arg_types_code(fd, dasm);
			dasm->size--;
		}
		handle_args(fd, dasm, code_op);
		dasm->arg_types = NULL;
	}
	if ((ret = read(fd, buf, 1)))
		error("Code size does not match");	
}