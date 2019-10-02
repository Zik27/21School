/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_translation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:19:42 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/06 11:42:35 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		*num_translation(char *square, int *figure, int i)
{
	if (square[i + 1] == '#')
		*figure++ = 1;
	if ((i + 2) < 20 && square[i + 2] == '#')
		*figure++ = 2;
	if ((i + 3) < 20 && square[i + 3] == '#' && square[i + 2] == '#')
		*figure++ = 3;
	else if ((i + 3) < 20 && square[i + 3] == '#')
		*figure++ = 8;
	if ((i + 4) < 20 && square[i + 4] == '#')
		*figure++ = 9;
	if ((i + 5) < 20 && square[i + 5] == '#')
		*figure++ = 10;
	if ((i + 6) < 20 && square[i + 6] == '#')
		*figure++ = 11;
	if ((i + 7) < 20 && square[i + 7] == '#')
		*figure++ = 12;
	if ((i + 9) < 20 && square[i + 9] == '#')
		*figure++ = 19;
	if ((i + 10) < 20 && square[i + 10] == '#')
		*figure++ = 20;
	if ((i + 11) < 20 && square[i + 11] == '#')
		*figure++ = 21;
	if ((i + 15) < 20 && square[i + 15] == '#')
		*figure++ = 30;
	return (figure - 3);
}

int		prepare_data(char *square, t_tetriminos_fig **head)
{
	int	i;
	int j;
	int	*figure_numb;
	int	*tmp;

	i = 0;
	j = 0;
	figure_numb = (int *)malloc(sizeof(int) * 4);
	if (!figure_numb)
		return (0);
	tmp = figure_numb;
	while (i < 20)
		if (square[i++] == '#')
		{
			figure_numb = num_translation(square, figure_numb, --i);
			break ;
		}
	if (!lst_push_back(head, figure_numb))
		return (0);
	free(tmp);
	return (1);
}
