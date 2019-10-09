/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:51:08 by djast             #+#    #+#             */
/*   Updated: 2019/10/08 18:42:23 by djast            ###   ########.fr       */
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

int		bytecode_to_int(unsigned char *buf, int count_bytes)
{
	int result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = buf[0] & 0b10000000;
	while (count_bytes)
	{
		if (sign)
			result += (buf[count_bytes - 1] ^ 0xFF) << (i++ * 8); // инвертирование
		else
			result += buf[count_bytes - 1] << (i++ * 8);
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

void	rewrite(t_vm_info *info, int addr, int number)
{
	int i;
	char *data;

	i = 4;
	data = int_to_bytecode(number, 4);
	printf("%s\n", data);
	while (i != 0)
	{
		info->map[addr + i - 1] = data[i - 1];
		i--;
	}
	free(data);
}

