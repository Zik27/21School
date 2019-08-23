/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:37:14 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/22 14:39:41 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_digits(char *str, int with_neg)
{
	int	i;

	i = 0;
	if (with_neg)
		if (str[i] == '-')
			i++;
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
	int		positive;
	char	*tmp;

	tmp = NULL;
	length = ft_strlen(str);
	if (str[0] == '+')
		positive = 1;
	else
		positive = 0;
	if (length > 11)
		return (0);
	else
	{
		tmp = ft_itoa(ft_atoi(str));
		if (ft_strcmp(tmp, str + positive) != 0)
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
	if (line[0] == '#' && line[1] == '#')
		error("Invalid number of ants");
	else if (line[0] == '#')
		return ;
	if (!check_digits(line, NO_NEG) || !check_intmax(line))
		error("Invalid number of ants");
	else
		map->count_ants = ft_atoi(line);
}
