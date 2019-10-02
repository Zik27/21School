/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:59:16 by vurrigon          #+#    #+#             */
/*   Updated: 2018/11/20 18:12:08 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	result;
	int	sqrt;

	result = 0;
	while ((nb + 1) / 2 >= result)
	{
		sqrt = result * result;
		if (sqrt == nb)
			return (result);
		result++;
	}
	return (0);
}
