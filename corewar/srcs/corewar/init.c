/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:58:35 by djast             #+#    #+#             */
/*   Updated: 2019/09/25 15:15:49 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ				*init_charp(int id)
{
	t_champ *champ;

	champ = (t_champ *)malloc(sizeof(t_champ));
	champ->id = id;
	champ->name = NULL;
	champ->comment = NULL;
	champ->code_size = -1;
	champ->code = NULL;
	champ->next = NULL;
	return (champ);
}