/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:11:12 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 13:15:11 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cerror(char *message, char *error_file)
{
	ft_printf(message);
	ft_printf(error_file);
	ft_printf("\n");
	exit(-1);
}


void	print_help(char **argv)
{
	ft_printf("Usage: ");
	ft_printf("%s [-dump nbr_cycles] [[-n number] champion1.cor] ...\n", argv[0]);
}

void		check_file(char *arg)
{
	int fd;
	char *byte;
	int size;

	byte = ft_strnew(1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		cerror("Can't read source file ", arg);
	size = read(fd, byte, 1);
	size = read(fd, byte, 1);
	printf("%x\n", byte[0]);

}

void		parse_args(int argc, char **argv)
{
	int i;
	char *find;

	i = 1;
	while (i < argc)
	{
		if ((find = ft_strstr(argv[i], ".cor")) != NULL && find[4] == '\0')
			check_file(argv[i]);
		else
			cerror("Can't read source file: ", argv[i]);
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc < 2)
	{
		print_help(argv);
		return (0);
	}
	parse_args(argc, argv);

	return (0);
}