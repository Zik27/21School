/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_translation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:19:42 by vurrigon          #+#    #+#             */
/*   Updated: 2019/01/03 21:08:22 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int		*num_translation(char *square, int *figure, int i)
{
	if (square[i + 1] == '#')
		*figure++ = 1;
	if (square[i + 2] == '#')
		*figure++ = 2;
	if (square[i + 3] == '#' && square[i + 2] == '#')
		*figure++ = 3;
	else if (square[i + 3] == '#')
		*figure++ = 8;
	if (square[i + 4] == '#')
		*figure++ = 9;
	if (square[i + 5] == '#')
		*figure++ = 10;
	if (square[i + 6] == '#')
		*figure++ = 11;
	if (square[i + 7] == '#')
		*figure++ = 12;
	if (square[i + 9] == '#')
		*figure++ = 19;
	if (square[i + 10] == '#')
		*figure++ = 20;
	if (square[i + 11] == '#')
		*figure++ = 21;
	if (square[i + 15] == '#')
		*figure++ = 30;
	return (figure - 3);
}

int		prepare_data(char *square)
{
	int	i;
	int j;
	int	*figure_numb;
	int	*tmp;
	static tetriminos_fig *head = NULL;

	i = 0;
	j = 0;
	figure_numb = (int *)malloc(sizeof(int) * 3 + 1);
	if (!figure_numb)
		return (0);
	tmp = figure_numb;
	while (i < 20)
		if (square[i++] == '#')
		{
			figure_numb = num_translation(square, figure_numb, --i);
			break ;
		}
	free(tmp);
	j = 0;
	while (j < 3)
		printf("fig = %d\n", figure_numb[j++]);
	lst_push_back(&head, figure_numb);

	tetriminos_fig	*current;
	current = head;
	while (current)
	{
		printf("%d\n", current->data[0]);
		printf("%d\n", current->data[1]);
		printf("%d\n", current->data[2]);
		printf("\n");

		current = current->next;
	}
	return (1);
}
