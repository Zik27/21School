/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:07:20 by djast             #+#    #+#             */
/*   Updated: 2019/11/06 16:24:20 by djast            ###   ########.fr       */
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
	{
		free(byte);
		return (NULL);
	}
	return (byte);
}

char	*get_champ_comment(int fd)
{
	char *byte;
	int size;

	byte = ft_strnew(2048);
	
	size = read(fd, byte, 2048);
	if (size != 2048)
	{
		free(byte);
		return (NULL);
	}
	return (byte);
}


int		get_champ_code_size(int fd)
{
	unsigned char *byte;
	int size;
	int code_size;

	byte = (unsigned char *)ft_strnew(4);
	size = read(fd, byte, 4);
	if (size != 4)
		return (-1);
	code_size = byte[3] + byte[2] * 16 * 16 + byte[1] * 16 * 16 * 16 * 16
								+ byte[0] * 16 * 16 * 16 * 16 * 16 * 16;
	free(byte);
	return (code_size);
}


char	*get_champ_name(int fd)
{
	char *byte;
	int size;

	byte = ft_strnew(128);
	
	size = read(fd, byte, 128);
	if (size != 128)
	{
		free(byte);
		return (NULL);
	}
	return (byte);
}
