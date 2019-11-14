/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:51:08 by djast             #+#    #+#             */
/*   Updated: 2019/11/13 18:20:59 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_player_count(t_champ *champs)
{
	int count;
	t_champ *cur_champ;

	count = 0;
	cur_champ = champs;
	while (cur_champ != NULL)
	{
		count++;
		cur_champ = cur_champ->next;
	}
	return (count);
}

t_champ		*find_player_by_id(t_champ *champs, int id)
{
	t_champ		*cur_champ;

	cur_champ = champs;
	while (cur_champ != NULL)
	{
		if (cur_champ->id == id)
			return (cur_champ);
		cur_champ = cur_champ->next;
	}
	return (NULL);
}

int		bytecode_to_int(t_vm_info *info, t_carriage *carr, int pos, int count_bytes)
{
	int result;
	int	i;
	int	sign;
	unsigned char *buff;

	(void) carr;
	buff = (unsigned char *)malloc(sizeof(unsigned char) * count_bytes);
	i = 0;
	while (i++ < count_bytes)
		buff[i - 1] = info->map[(pos + i - 1) % MEM_SIZE];
	// ft_printf("buff: %x%x%x%x\n", buff[0], buff[1], buff[2], buff[3]);
	result = 0;
	i = 0;
	sign = buff[0] & 0b10000000;
	while (count_bytes)
	{
		if (sign)
			result += (buff[count_bytes - 1] ^ 0xFF) << (i++ * 8); // инвертирование
		else
			result += buff[count_bytes - 1] << (i++ * 8);
		count_bytes--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

char	*int_to_bytecode(int value, int size)
{
	int8_t		i;
	char		*data;

	i = 0;
	data = ft_strnew(size);
	while (size)
	{
		data[size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
	return (data);
}

void	create_carr_copy(t_vm_info *info, t_carriage *carr)
{
 	t_carriage *new_carr;
 	int i;

 	new_carr = init_carriage(carr->champ, info);

	i = 0;
	while (i++ < REG_NUMBER)
		new_carr->registers[i - 1] = carr->registers[i - 1];

	new_carr->carry = carr->carry;
	new_carr->cycle_last_live = carr->cycle_last_live;

	new_carr->next = info->carriages;
	info->carriages = new_carr;
}
