/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:05:40 by vurrigon          #+#    #+#             */
/*   Updated: 2019/06/30 14:23:24 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
int	check_max(char *str)
{
	int	length;
	int	positive;

	length = ft_strlen(str);
	if (str[0] == '+')
		positive = 1;
	else
		positive = 0;
	if (length > 11)
		return (0);
	else if (((str[0] == '-' || str[0] == '+') && length == 11) || length == 10)
		if (ft_strcmp(ft_itoa(ft_atoi(str)), str + positive) != 0)
			return (0);
	return (1);
}

int	check_dup(char **str)
{
	int i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_atoi(str[j]) == ft_atoi(str[i]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);

}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (i == 0)
				i++;
			else
				return (0);
		}
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isnumber(str[i]) || !check_max(str[i]))
			return (0);
		i++;
	}
	if (!check_dup(str))
		return (0);
	return (1);
}