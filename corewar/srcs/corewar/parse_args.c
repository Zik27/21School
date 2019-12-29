/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 13:30:29 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 13:52:07 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*parse_args(int argc, char **argv, t_sdl **sdl, t_vm_info *info)
{
	int		i;
	char	*find;
	t_champ	*champs;
	int		id;
	t_champ *cur_champ;

	i = 1;
	id = 1;
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
			if (is_flag(argv[i + 1], argv[i + 2], get_argv_cor(argv), champs) == 1)
			{
				parse_champion(&champs, &cur_champ, argv[i + 2],
									ft_atoi(argv[i + 1]));
				i += 2;
			}
			else
				cerror("Wrong place to put player", NULL);
		}
		else if ((find = ft_strstr(argv[i], "-v")) != NULL && find[2] == '\0'
					&& *sdl == NULL)
			*sdl = init_sdl();
		else
			cerror("Can't read source file %s", argv[i]);
		i++;
	}
	set_champion_id(champs);
	return (champs);
}
