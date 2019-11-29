/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:50:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/19 15:27:52 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_extension(char *filename)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(filename, '.');
	while (tmp[i + 1])
		i++;
	if (!ft_strcmp(tmp[i], "s"))
	{
		free_split(tmp);
		return (1);
	}
	else if (!ft_strcmp(tmp[i], "cor"))
	{
		free_split(tmp);
		return (-1);
	}
	free_split(tmp);
	return (0);
}

void	check_end_file(t_player *player)
{
	char	buf[2];
	int		lpos;
	int		end;

	end = lseek(player->fd, 0, SEEK_END);
	lpos = end;
	while (lpos-- > 0)
	{
		lseek(player->fd, lpos, SEEK_SET);
		read(player->fd, buf, 1);
		if (is_whitespace(*buf))
			continue;
		else if (*buf == '\n')
			return ;
		else
		{
			check_comment(player->fd, lpos, buf);
			return ;
		}
	}
}

void	assemble(int fd, char *file_name)
{
	t_player	*header;
	int			new_fd;

	if (!(header = init_player(fd, file_name)))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
	reading_body_champion(fd, header);
	calculate_size_exec_code(header);
	check_arg_is_digit(header);
	check_end_file(header);
	new_fd = create_file_bytecode(header);
	translate_to_bytecode(header, new_fd);
	ft_putstr("Writing output program to ");
	ft_putendl(header->file_name);
	free_asm(header);
}

int		main(int argc, char **argv)
{
	int	fd;
	int	exten;

	if (argc != 2)
		error("Usage: ./asm <sourcefile.s> | <sourcefile.cor>");
	else if (!(exten = check_extension(argv[1])))
		error("Invalid file extension");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error("File name missing.");
		if (exten == 1)
			assemble(fd, argv[1]);
	}
	return (0);
}
