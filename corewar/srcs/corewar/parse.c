/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:21:23 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 15:52:53 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_champion(t_champ **champs, t_champ **cur_champ,
								char *filename, int i)
{
	t_champ	*tmp;

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

void		parse_dump_flag(char *command, char *argv_cycle, t_vm_info *info)
{
	int		cycle;
	char	*check;

	cycle = ft_atoi(argv_cycle);
	check = ft_itoa(cycle);
	if (ft_strcmp(argv_cycle, check) != 0 || cycle < 0)
		cerror("Wrong -dump (-d) cycle: %s", argv_cycle);
	else if (info->dump_cycle >= 0)
		cerror("Many -dump (-d) flags", NULL);
	info->dump_cycle = cycle;
	if (ft_strcmp(command, "-d") == 0)
		info->dump_type = CODE_D;
	else
		info->dump_type = CODE_DUMP;
	free(check);
}

int			is_flag(char *place, char *name, int max_players, t_champ *champs)
{
	int		int_place;
	char	*find;

	int_place = ft_atoi(place);
	if (int_place > max_players || find_player_by_id(champs, int_place) != 0 ||
		int_place < 1 || (find = ft_strstr(name, ".cor")) == NULL ||
		find[4] != '\0')
		return (0);
	return (1);
}

int			get_argv_cor(char **argv)
{
	int		i;
	int		count;
	char	*find;

	i = 1;
	count = 0;
	while (argv[i] != '\0')
	{
		if ((find = ft_strstr(argv[i], ".cor")) != NULL && find[4] == '\0')
			count++;
		i++;
	}
	return (count);
}

void		set_champion_id(t_champ *champs)
{
	int		id;
	t_champ	*cur_champ;

	id = 1;
	cur_champ = champs;
	while (cur_champ != NULL)
	{
		while (cur_champ->id == -1)
		{
			if (find_player_by_id(champs, id) == NULL)
				cur_champ->id = id;
			id++;
		}
		cur_champ = cur_champ->next;
	}
}
