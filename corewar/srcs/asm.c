/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:50:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/18 17:00:40 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

int		check_extension(char *filename)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(filename, '.');
	while (tmp[i + 1])
		i++;
	if (ft_strcmp(tmp[i], "s") == 0)
		return (1);
	return (0);
}

void	error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void	name_check_and_record(char *name, t_player *player)
{
	int	length;

	length = ft_strlen(name) - 2;
	if (length > PROG_NAME_LENGTH)
		error("Champion name too long (Max length 128)");
	player->name = ft_strsub(name, 1, length);
}

void	comment_check_and_record(char *comment, t_player *player)
{
	int	length;

	length = ft_strlen(comment) - 2;
	if (length > COMMENT_LENGTH)
		error("Champion comment too long (Max length 2048)");
	player->comment = ft_strsub(comment, 1, length);
}

int		check_name_comment(int fd, t_player *player)
{
	char	*line;
	char	*find;

	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == '\n' || line[0] == COMMENT_CHAR ||
			line[0] == ALT_COMMENT_CHAR)
			continue ;
		else if (ft_strstr(line, NAME_CMD_STRING) && (find = ft_strchr(line, '"')))
			name_check_and_record(find, player);
		else if (ft_strstr(line, COMMENT_CMD_STRING) && (find = ft_strchr(line, '"')))
			comment_check_and_record(find, player);
		else
			error("Error name - comment");
		if (player->comment && player->name)
			return (1);
		free(line);
	}
	return (0);
}

t_player	*init_player()
{
	t_player *player;

	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->name = NULL;
	player->comment = NULL;
	//player->commands = NULL;
	return (player);
}

void	read_operations(int fd, t_player *player)
{
	char *line;

	player++;
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == '\n' || line[0] == COMMENT_CHAR ||
			line[0] == ALT_COMMENT_CHAR)
			continue ;
	}
}

void	read_champion(int fd)
{
	t_player *header;

	if (!(header = init_player()))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
	read_operations(fd, header);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		error("Usage: ./asm <sourcefile.s>");
	else if (!check_extension(argv[1]))
		error("Invalid file extension");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error("File name missing.");
		read_champion(fd);
	}
	return (0);
}
