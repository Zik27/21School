/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:37:14 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/20 16:41:17 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

int		check_intmax(char *str)
{
	int		length;
	char	*tmp;

	tmp = NULL;
	length = ft_strlen(str);
	if (length > 10)
		return (0);
	else
	{
		tmp = ft_itoa(ft_atoi(str));
		if (ft_strcmp(tmp, str) != 0)
		{
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	return (1);
}

void	count_ants(char *line, t_map *map)
{
	if (line[0] == '#')
		return ;
	if (!check_digits(line) || !check_intmax(line))
		return ;
	else
		map->count_ants = ft_atoi(line);
}
