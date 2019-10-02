/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:13:08 by djast             #+#    #+#             */
/*   Updated: 2019/10/02 14:54:15 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		*get_op_arg()
{
	return (NULL);
}

void	make_command_live(t_vm_info *info, t_carriage *carr)
{
	char *player_id;

	player_id = get_op_arg();
	info->live++;
	carr->cycle_last_live = info->cycle;
}
