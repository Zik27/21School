/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:21:23 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 19:30:53 by djast            ###   ########.fr       */
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

void		set_champion_id(t_champ	*champs)
{
	int id;
	t_champ *cur_champ;

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

t_champ		*parse_args(int argc, char **argv, t_sdl **sdl, t_vm_info *info)
{
	int		i;
	char	*find;
	t_champ	*champs;
	int		id;
	int		count_players;
	t_champ *cur_champ;

	i = 1;
	id = 1;
	count_players = get_argv_cor(argv);
	champs = NULL;
	while (i < argc)
	{
		while (find_player_by_id(champs, id) != 0)
			id++;
		if ((find = ft_strstr(argv[i], ".cor")) != NULL && find[4] == '\0')
			parse_champion(&champs, &cur_champ, argv[i], -1);
		else if (ft_strcmp(argv[i], "-d") == 0 ||
							ft_strcmp(argv[i], "-dump") == 0)
		{
			if (i + 1 >= argc)
				cerror("No dump cycle", NULL);
			parse_dump_flag(argv[i], argv[i + 1], info);
			i++;
		}
		else if (ft_strcmp(argv[i], "-debug") == 0)
			info->debug_flag = 1;
		else if (ft_strcmp(argv[i], "-n") == 0)
		{
			if (i + 2 >= argc)
				cerror("Wrong -n flag", NULL);
			if (is_flag(argv[i + 1], argv[i + 2], count_players, champs) == 1)
			{
				parse_champion(&champs, &cur_champ, argv[i + 2],
									ft_atoi(argv[i + 1]));
				i += 2;
			}
			else
				cerror("Wrong place to put player", NULL);
		}
		else if ((find = ft_strstr(argv[i], "-v")) != NULL && find[2] == '\0' && *sdl == NULL)
			*sdl = init_sdl();
		else
			cerror("Can't read source file %s", argv[i]);
		i++;
	}
	set_champion_id(champs);
	return (champs);
}
