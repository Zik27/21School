/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:21:23 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 16:16:43 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_args(int argc, char **argv)
{
	int i;
	char *find;
	t_champ *champs;
	t_champ *tmp;

	i = 1;
	while (i < argc)
	{
		if ((find = ft_strstr(argv[i], ".cor")) != NULL && find[4] == '\0')
		{
			if (champs == NULL)
				champs = check_file(argv[i], i);
			else
			{
				tmp = check_file(argv[i], i);
				tmp->next = champs;
				champs = tmp;
			}

		}
		else
			cerror("Can't read source file %s", argv[i]);
		i++;
	}
}
