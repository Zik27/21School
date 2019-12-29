/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 13:30:29 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 15:53:49 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			parse_dump(int argc, char **argv, t_vm_info *info, int *i)
{
	if (ft_strcmp(argv[*i], "-d") == 0 ||
						ft_strcmp(argv[*i], "-dump") == 0)
	{
		if (*i + 1 >= argc)
			cerror("No dump cycle", NULL);
		parse_dump_flag(argv[*i], argv[*i + 1], info);
		(*i)++;
	}
	else
		return (0);
	return (1);
}

int			parse_with_champ(int argc, char **argv, t_vm_info *info, int *i)
{
	char	*find;

	if ((find = ft_strstr(argv[*i], ".cor")) != NULL && find[4] == '\0')
		parse_champion(&(info->champs), &(info->cur_champ), argv[*i], -1);
	else if (ft_strcmp(argv[*i], "-n") == 0)
	{
		if (*i + 2 >= argc)
			cerror("Wrong -n flag", NULL);
		if (is_flag(argv[*i + 1], argv[*i + 2], get_argv_cor(argv),
															info->champs) == 1)
		{
			parse_champion(&(info->champs), &(info->cur_champ), argv[*i + 2],
								ft_atoi(argv[*i + 1]));
			*i += 2;
		}
		else
			cerror("Wrong place to put player", NULL);
	}
	else
		return (0);
	return (1);
}

int			parse_ext_flags(char **argv, t_vm_info *info, int *i)
{
	char	*find;

	if (ft_strcmp(argv[*i], "-debug") == 0)
		info->debug_flag = 1;
	else if ((find = ft_strstr(argv[*i], "-v")) != NULL && find[2] == '\0'
				&& info->sdl == NULL)
		info->sdl = init_sdl();
	else
		return (0);
	return (1);
}

t_champ		*parse_args(int argc, char **argv, t_vm_info *info)
{
	int		i;
	int		id;

	i = 1;
	id = 1;
	while (i < argc)
	{
		while (find_player_by_id(info->champs, id) != 0)
			id++;
		if (parse_dump(argc, argv, info, &i) == 1 ||
			parse_with_champ(argc, argv, info, &i) == 1 ||
			parse_ext_flags(argv, info, &i) == 1)
		{
			i++;
			continue ;
		}
		else
			cerror("Can't read source file %s", argv[i]);
		i++;
	}
	set_champion_id(info->champs);
	return (info->champs);
}
