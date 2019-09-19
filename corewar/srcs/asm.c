/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:50:59 by vurrigon          #+#    #+#             */
/*   Updated: 2019/09/19 18:20:29 by vurrigon         ###   ########.fr       */
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

int	skip_tab_space(t_player *player, char *line)
{
	while (line[player->num_col])
	{
		if (line[player->num_col] == ' ' || line[player->num_col] == '\t')
			player->num_col++;
		else if (line[player->num_col] == '"')
			return (QUOTE);
		else
			return (-1);
	}
	return (0);
}

void	write_name(t_player *player, char *line)
{
	char	*tmp;
	int		length;

	if (skip_tab_space(player, line) != QUOTE)
		error_file("Syntax error", player->num_col + 1, player->num_row);
	player->num_col++;
	tmp = ft_strchr(&line[player->num_col], '"');
	if (!tmp)
		error_file("Invalid name", player->num_col + 1, player->num_row);
	length = tmp - &line[player->num_col];
	if (length > PROG_NAME_LENGTH)
 		error("Champion name too long (Max length 128)");
 	tmp = &line[player->num_col];
 	player->num_col += length + 1;
 	if (skip_tab_space(player, line) && !is_comment(line, player))
 		error_file("Syntax error", player->num_col + 1, player->num_row);
 	player->name = ft_strndup(tmp, length);
 	printf("[%s]\n", player->name);
}

void	write_comment(t_player *player, char *line)
{
	char	*tmp;
	int		length;

	if (skip_tab_space(player, line) != QUOTE)
		error_file("Syntax error", player->num_col + 1, player->num_row);
	player->num_col++;
	tmp = ft_strchr(&line[player->num_col], '"');
	if (!tmp)
		error_file("Invalid comment", player->num_col + 1, player->num_row);
	length = tmp - &line[player->num_col];
	if (length > COMMENT_LENGTH)
		error("Champion comment too long (Max length 2048)");
 	tmp = &line[player->num_col];
 	player->num_col += length + 1;
 	if (skip_tab_space(player, line) && !is_comment(line, player))
 		error_file("Syntax error", player->num_col + 1, player->num_row);
 	player->comment = ft_strndup(tmp, length);
 	printf("[%s]\n", player->comment);
}

int		check_command(char *line, t_player *player)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, 5) && (line[5] == '\t' || line[5] == ' '))
	{
		player->num_col += OFFSET_CMD_NAME;
		write_name(player, line);
		return (1);
	}
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8) && (line[8] == '\t' || line[8] == ' '))
	{
		player->num_col += OFFSET_CMD_COMMENT;
		write_comment(player, line);
		return (1);
	}
	return (0);

}

void	search_comment_name(t_player *player, char *line)
{
	while (line[player->num_col])
	{
		if (is_comment(line, player))
			return ;
		else if (line[player->num_col] == '.')
		{
			if (!check_command(&line[player->num_col], player))
				error_file("Unknown command", player->num_col + 1, player->num_row);
			return ;
		}
		else if (line[player->num_col] != ' ' && line[player->num_col] != '\t')
			error_file("Syntax error", player->num_col + 1, player->num_row);		
		player->num_col++;
	}
}

int		check_name_comment(int fd, t_player *player)
{
	char	*line;
	//char	*find;

	while (get_next_line(fd, &line) == 1)
	{
		player->num_row++;
		if (!player->comment || !player->name)
			search_comment_name(player, line);
		else
			return (1);
		player->num_col = 0;
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
	player->num_row = 0;
	player->num_col = 0;
	//player->commands = NULL;
	return (player);
}

void	read_champion(int fd)
{
	t_player *header;

	if (!(header = init_player()))
		error("Error allocating header memory");
	if (!check_name_comment(fd, header))
		error("Error reading of name or comment");
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
