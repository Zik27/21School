/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:11:32 by vurrigon          #+#    #+#             */
/*   Updated: 2019/12/29 16:00:19 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int		create_new_fd(t_dasm *dasm)
{
	char	*new_name;
	char	*tmp;
	int		fd;

	new_name = ft_strstr(dasm->full_name_file, ".cor");
	tmp = ft_strsub(dasm->full_name_file, 0, new_name - dasm->full_name_file);
	new_name = ft_strjoin(tmp, ".s");
	free(tmp);
	fd = open(new_name, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		open(new_name, O_CREAT);
		fd = open(new_name, O_WRONLY);
	}
	dasm->full_name_file = new_name;
	return (fd);
}

void	write_name_comment(t_dasm *dasm, int fd)
{
	ft_putstr_fd(NAME_CMD_STRING, fd);
	ft_putstr_fd("\t\t\"", fd);
	ft_putstr_fd(dasm->name, fd);
	ft_putstr_fd("\"\n", fd);
	ft_putstr_fd(COMMENT_CMD_STRING, fd);
	ft_putstr_fd("\t\"", fd);
	ft_putstr_fd(dasm->comment, fd);
	ft_putstr_fd("\"\n\n", fd);
}

void	write_commands(t_dasm *dasm, int new_fd)
{
	t_inst_dasm *commands;
	t_args_dasm	*arg;

	commands = dasm->instr;
	while (commands)
	{
		ft_putstr_fd(commands->name, new_fd);
		ft_putstr_fd(" ", new_fd);
		arg = commands->args;
		while (arg)
		{
			ft_putstr_fd(arg->data, new_fd);
			if (arg->next)
				ft_putstr_fd(", ", new_fd);
			else
				ft_putstr_fd("\n", new_fd);
			arg = arg->next;
		}
		commands = commands->next;
	}
}
