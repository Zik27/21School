/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:05:40 by vurrigon          #+#    #+#             */
/*   Updated: 2019/03/29 16:40:50 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			{
				i++;
				continue ;
			}
			else
				return (0);
		}
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid(char **str, int count)
{
	int	i;

	count++;
	i = 1;
	while (str[i])
	{
		if (!ft_isnumber(str[i]))
			return (0);
		i++;
	}
	return (1);
}