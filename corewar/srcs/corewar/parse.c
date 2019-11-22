/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:21:23 by djast             #+#    #+#             */
/*   Updated: 2019/11/22 17:00:34 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_champion(t_champ **champs, t_champ **cur_champ, char *filename, int i)
{
	t_champ *tmp;

	tmp = check_file(filename, i);
	if ((*champs) == NULL)
	{
		(*champs) = tmp;
		(*cur_champ) = (*champs);
	}
	else
	{
		(*cur_champ)->next = tmp;
		(*cur_champ) = (*cur_champ)->next;
	}
}

void		parse_dump_flag(char *argv_cycle, t_vm_info *info)
{
	int cycle;
	char *check;

	cycle = ft_atoi(argv_cycle);
	check = ft_itoa(cycle);
	if (ft_strcmp(argv_cycle, check) != 0 || cycle < 0)
		cerror("Wrong -dump (-d) cycle: %s", argv_cycle);
	else if (info->dump_cycle >= 0)
		cerror("Many -dump (-d) flags", NULL);
	info->dump_cycle = cycle;
}


t_champ		*parse_args(int argc, char **argv, t_vm_info *info)
{
	int i;
	char *find;
	t_champ *champs;
	int id;
	
	t_champ *cur_champ;
	i = 1;
	id = 1;
	champs = NULL;
	while (i < argc)
	{
		if ((find = ft_strstr(argv[i], ".cor")) != NULL && find[4] == '\0')
			parse_champion(&champs, &cur_champ, argv[i], id++);
		else if (ft_strcmp(argv[i], "-d") == 0)
			parse_dump_flag(argv[i++ + 1], info);
		else
			cerror("Can't read source file %s", argv[i]);
		i++;
	}
	return (champs);
}
