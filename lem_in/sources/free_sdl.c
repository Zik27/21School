/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:13:43 by djast             #+#    #+#             */
/*   Updated: 2019/09/13 15:41:16 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_ants(t_ants *ants)
{
	t_ants	*tmp;

	while (ants)
	{
		tmp = ants;
		ants = ants->next;
		free(tmp);
	}
}

void	free_links(t_links *links)
{
	t_links	*tmp;

	while (links)
	{
		tmp = links;
		links = links->next;
		free(tmp);
	}
}