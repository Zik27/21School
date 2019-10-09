/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:42:19 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/09 13:44:18 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void	disassemble(int fd, char *full_name)
{
	t_dasm	*dasm;
	int		new_fd;

	if (check_magic_header(fd) != COREWAR_EXEC_MAGIC)
		error("Invalid magic header");
	if (!(dasm = init_dasm(full_name)))
		error("Memory allocation error");
	dasm->name = get_name(fd);
	check_null(fd, 4);
	dasm->size = get_exec_size(fd);
	dasm->comment = get_comment(fd);
	check_null(fd, 4);
	handling_command(fd, dasm);
	new_fd = create_new_fd(dasm);
	write_name_comment(dasm, new_fd);
	write_commands(dasm, new_fd);
	ft_putstr("Writing output program to ");
	ft_putendl(dasm->full_name_file);
	free_dasm(dasm);
}
