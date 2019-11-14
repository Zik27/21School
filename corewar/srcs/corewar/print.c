/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:20:31 by djast             #+#    #+#             */
/*   Updated: 2019/11/13 18:37:50 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cerror(char *message, char *error_file)
{
	ft_printf(message, error_file);
	ft_printf("\n");
	exit(-1);
}

void	print_help(char **argv)
{
	ft_printf("Usage: ");
	ft_printf("%s [-dump nbr_cycles] [[-n number] champion1.cor] ...\n", argv[0]);
}

void	print_map(char *map)
{
	int symbol;

	symbol = 0;
	while (symbol != MEM_SIZE)
	{
		if (symbol == 3343)
			ft_printf("HERE --> ");
		ft_printf("%.2x ", map[symbol] & 0xFF);
		symbol++;
		if ((symbol) % 64 == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
}

void	print_carriages(t_carriage *car)
{
	t_carriage *cur_car;

	cur_car = car;
	while (cur_car != NULL)
	{
		ft_printf("---------------------------------\n");
		ft_printf("Carriade %d:\nCarry: %d, op_code: %d\n", cur_car->id, cur_car->carry,
														cur_car->op_code);
		ft_printf("Cycle_last_live: %d, op_steps: %d\n", cur_car->cycle_last_live,
															cur_car->op_steps);
		ft_printf("Cur_pos: %d, reg1: %d\n", cur_car->cur_pos, cur_car->registers[0]); 
		ft_printf("reg2: %d, reg2: %d, reg3: %d\n", cur_car->registers[1], cur_car->registers[2], cur_car->registers[3]);
		cur_car = cur_car->next;
	}
	ft_printf("---------------------------------\n");
}

void	introducing(t_champ	*champs, t_vm_info *info)
{
	int		count;
	t_champ	*player;

	count = 1;
	ft_printf("Introducing contestants...\n");
	while (count != info->count_players + 1)
	{
		player = find_player_by_id(champs, count);
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				player->id, player->code_size, player->name, player->comment);
		count++;
	}

}