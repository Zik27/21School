/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:21:23 by djast             #+#    #+#             */
/*   Updated: 2019/10/09 09:53:40 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*parse_args(int argc, char **argv)
{
	int i;
	char *find;
	t_champ *champs;
	t_champ *tmp;
	t_champ *cur_champ;

	i = 1;
	champs = NULL;
	while (i < argc)
	{
		if ((find = ft_strstr(argv[i], ".cor")) != NULL && find[4] == '\0')
		{
			if (champs == NULL)
			{
				champs = check_file(argv[i], i);
				cur_champ = champs;
			}
			else
			{
				tmp = check_file(argv[i], i);
				cur_champ->next = tmp;
				cur_champ = cur_champ->next;
			}

		}
		else
			cerror("Can't read source file %s", argv[i]);
		i++;
	}
	return (champs);
}
