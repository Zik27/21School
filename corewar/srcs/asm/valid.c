/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:18:24 by vurrigon          #+#    #+#             */
/*   Updated: 2019/10/01 11:28:23 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int		check_magic_header(int fd)
{
	int				ret;
	unsigned char	buf[4];

	ret = read(fd, buf, 4);
	if (ret < 4)
		error("Invalid file: error reading magic header");
	return (bytecode_to_int(buf, 4));
}

void	check_null(int fd, int bytes)
{
	int				ret;
	unsigned char	buf[bytes];

	ret = read(fd, buf, bytes);
	if (ret < bytes)
		error("Invalid file: error reading NULL control octets");
	while (bytes > 0)
	{
		if (buf[bytes - 1])
			error("Invalid NULL control octets");
		bytes--;
	}
}

char	*get_name(int fd)
{
	int	ret;
	unsigned char	buf[PROG_NAME_LENGTH];
	char	*result;
	int		i;

	i = 0;
	ret = read(fd, buf, PROG_NAME_LENGTH);
	if (ret < PROG_NAME_LENGTH)
		error("Invalid file: error reading champion's name");
	result = ft_strnew(PROG_NAME_LENGTH);
	while (buf[i])
	{
		result[i] = buf[i];
		i++;
	}
	return (result);
}

char	*get_comment(int fd)
{
	int	ret;
	unsigned char	buf[COMMENT_LENGTH];
	char	*result;
	int		i;

	i = 0;
	ret = read(fd, buf, COMMENT_LENGTH);
	if (ret < COMMENT_LENGTH)
		error("Invalid file: error reading champion's comment");
	result = ft_strnew(COMMENT_LENGTH);
	while (buf[i])
	{
		result[i] = buf[i];
		i++;
	}
	return (result);
}


void	get_types(t_dasm *dasm, unsigned char types)
{
	int				size;
	unsigned char	*types_code;
	int				i;
	int				divider;

	divider = 0b11000000;
	i = 0;
	size = count_args(types);
	if (size == -1)
		error("Invalid arg types code");
	types_code = (unsigned char	*)malloc((size + 1) * sizeof(unsigned char));
	while (size--)
	{
		types_code[i] = ((divider & types) >> (6 - 2 * i));
		i++;
		divider /= 4;
	}
	types_code[i] = '\0';
	dasm->arg_types = types_code;
}