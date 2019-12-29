/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:20:31 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 12:39:34 by vurrigon         ###   ########.fr       */
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
	ft_printf("%s [-dump nbr_cycles] [[-n number] champion1.cor] ...\n",
																	argv[0]);
	exit(0);
}

void	print_map(char *map, int count_in_row)
{
	int symbol;
	int row;

	symbol = 0;
	row = 0;
	ft_printf("0x0000 : ");
	while (symbol != MEM_SIZE)
	{
		ft_printf("%.2x ", map[symbol] & 0xFF);
		symbol++;
		if ((symbol) % count_in_row == 0 && symbol != 4096)
		{
			row += count_in_row;
			ft_printf("\n");
			ft_printf("%#.4x : ", row);
		}
	}
	ft_printf("\n");
}

void	print_carriages(t_carriage *car)
{
	t_carriage *cur_c;

	cur_c = car;
	while (cur_c != NULL)
	{
		ft_printf("---------------------------------\n");
		ft_printf("Carriade %d:\nCarry: %d, op_code: %d\n", cur_c->id,
											cur_c->carry, cur_c->op_code);
		ft_printf("Cycle_last_live: %d, op_steps: %d\n",
								cur_c->cycle_last_live, cur_c->op_steps);
		ft_printf("Cur_pos: %d, reg1: %d\n",
									cur_c->cur_pos, cur_c->registers[0]);
		ft_printf("reg2: %d, reg2: %d, reg3: %d\n",
			cur_c->registers[1], cur_c->registers[2], cur_c->registers[3]);
		cur_c = cur_c->next;
	}
	ft_printf("---------------------------------\n");
}

void	introducing(t_champ *champs, t_vm_info *info)
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
