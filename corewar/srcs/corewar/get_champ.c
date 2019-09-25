/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:07:20 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 16:17:04 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*get_champ_code(int fd, int code_size)
{
	char *byte;
	int size;

	byte = ft_strnew(code_size + 1);
	
	size = read(fd, byte, code_size + 1);
	if (size != code_size)
		return (NULL);
	return (byte);
}

char	*get_champ_comment(int fd)
{
	char *byte;
	int size;

	byte = ft_strnew(2048);
	
	size = read(fd, byte, 2048);
	return (byte);
}


int		get_champ_code_size(int fd)
{
	char *byte;
	int size;
	int code_size;

	byte = ft_strnew(4);
	size = read(fd, byte, 4);
	code_size = byte[3] + byte[2] * 16 * 16 + byte[1] * 16 * 16 * 16 * 16
								+ byte[0] * 16 * 16 * 16 * 16 * 16 * 16;
	return (code_size);
}


char	*get_champ_name(int fd)
{
	char *byte;
	int size;

	byte = ft_strnew(128);
	
	size = read(fd, byte, 128);
	return (byte);
}
