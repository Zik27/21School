/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 15:24:14 by vurrigon          #+#    #+#             */
/*   Updated: 2019/08/22 14:40:10 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_duplicates(t_room *rooms, char **room)
{
	t_room	*tmp;

	tmp = rooms;
	if (!tmp->next && !tmp->name && !tmp->x && !tmp->y)
		return (1);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, room[0]) == 0 || (ft_atoi(room[1]) == tmp->x &&
			ft_atoi(room[2]) == tmp->y))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	add_room(char **room, t_room *rooms)
{
	t_room	*tmp;
	t_room	*new_room;

	tmp = rooms;
	if (!tmp->next && tmp->name == NULL)
	{
		tmp->name = room[0];
		tmp->x = ft_atoi(room[1]);
		tmp->y = ft_atoi(room[2]);
	}
	else
	{
		new_room = init_room(room[0], ft_atoi(room[1]), ft_atoi(room[2]));
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_room;
	}
}

void	parse_rooms(char *str, t_map *map, t_room *rooms)
{
	char	**room;
	int		i;

	i = 1;
	room = ft_strsplit(str, ' ');
	if (room[0][0] == 'L' || ft_strchr(room[0], '-'))
			error("Invalid room name");
	while (room[i])
	{
		if (!check_digits(room[i], WITH_NEG) || !check_intmax(room[i]))
			error("Invalid coordinates");
		i++;
	}
	if (i != 3)
		error("Invalid room");
	if (!check_duplicates(rooms, room))
		error("Duplicates detected");
	add_room(room, rooms);

}
