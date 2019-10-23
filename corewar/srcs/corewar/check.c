/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:38:07 by djast             #+#    #+#             */
/*   Updated: 2019/10/23 13:54:45 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		check_magic_number(int fd)
{
	char *byte;
	int size;
	int magic_number;

	byte = ft_strnew(4);
	
	size = read(fd, byte, 4);
	if (size != 4)
		return (0);
	magic_number = (byte[3] & 0xFF) + (byte[2] & 0xFF) * 16 * 16
			+ (byte[1] & 0xFF) * 16 * 16 * 16 * 16
			+ (byte[0] & 0xFF) * 16 * 16 * 16 * 16 * 16 * 16;
	if (magic_number == COREWAR_EXEC_MAGIC)
	{
		free(byte);
		return (1);
	}
	free(byte);
	return (0);
}

static int		check_null(int fd, int size)
{
	char *byte;
	int size_read;

	byte = ft_strnew(size);
	size_read = read(fd, byte, size);
	if (size_read != 4)
		return (0);
	if ((byte[0] & 0xFF) == 0x0 && (byte[1] & 0xFF) == 0x0 &&
		(byte[2] & 0xFF) == 0x0 && (byte[3] & 0xFF) == 0x0)
	{
		free(byte);
		return (1);
	}
	free(byte);
	return (0);
}

t_champ			*check_file(char *arg, int id)
{
	int fd;
	t_champ *champ;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		cerror("Can't read source file %s", arg);
	if (!check_magic_number(fd))
		cerror("Error: File %s has an invalid header", arg);
	champ = init_champ(id);
	champ->name = get_champ_name(fd);
	if (!check_null(fd, 4))
		cerror("Error: File %s has an invalid header", arg);
	champ->code_size = get_champ_code_size(fd);
	champ->comment = get_champ_comment(fd);
	if (!check_null(fd, 4))
		cerror("Error: File %s has an invalid header", arg);
	if ((champ->code = get_champ_code(fd, champ->code_size)) == NULL)
		cerror("Error: File %s has a code size that differ from what its header says", arg);
	if (champ->code_size > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n",
				arg, champ->code_size, CHAMP_MAX_SIZE);
		exit(-1);
	}
	return (champ);
}

int		check_cycle_to_die(t_vm_info *info)
{
	(void) info;
	//printf("%d\n", info->cycle);
	delete_death_carr(info, info->carriages);
	if (info->carriages == NULL)
	{
		ft_printf("ENDGAME\n");
		ft_printf("Winner: %s\n", info->last_live_player->name);
		return (1);
	}
	return (0);
}
