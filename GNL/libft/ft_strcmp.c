/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:49:34 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:22:33 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int a;

	a = 0;
	while (s1[a] && s2[a] && (unsigned char)s1[a] == (unsigned char)s2[a])
		a++;
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
