/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 13:13:51 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 13:23:25 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				draw_map_symbol(t_sdl *sdl, char text, SDL_Rect r,
										SDL_Color color)
{
	char *data;

	data = ft_strnew(2);
	data[0] = (text & 0xFF) / 16 > 9 ? (text & 0xFF) / 16 + '7' :
									(text & 0xFF) / 16 + '0';
	data[1] = (text & 0xFF) % 16 > 9 ? (text & 0xFF) % 16 + '7' :
									(text & 0xFF) % 16 + '0';
	sdl->surface = TTF_RenderText_Solid(sdl->font, data, color);
	SDL_DestroyTexture(sdl->text);
	sdl->text = SDL_CreateTextureFromSurface(sdl->renderer,
													sdl->surface);
	SDL_FreeSurface(sdl->surface);
	SDL_RenderCopy(sdl->renderer, sdl->text, NULL, &r);
	free(data);
}

static SDL_Color	*get_color(int color_map)
{
	SDL_Color	*c;

	if (color_map == 1)
		c = create_sdl_color(0, 0, 173, 0);
	else if (color_map == 2)
		c = create_sdl_color(173, 0, 0, 0);
	else if (color_map == 3)
		c = create_sdl_color(0, 173, 0, 0);
	else
		c = create_sdl_color(128, 128, 128, 0);
	return (c);
}

void				draw_map(t_sdl *sdl, t_vm_info *info)
{
	int			i;
	int			j;
	SDL_Rect	*r;
	SDL_Color	*c;

	i = 0;
	j = 0;
	while (i + (j * 64) < MEM_SIZE)
	{
		c = get_color(info->color_map[i + j * 64]);
		r = create_sdl_rect(10 + i * (SYMBOL_SIZE + SPACE_SIZE), 10 + j *
				(SYMBOL_SIZE + SPACE_SIZE), SYMBOL_SIZE, SYMBOL_SIZE);
		draw_map_symbol(sdl, info->map[i + j * 64], *r, *c);
		i++;
		if (i % 64 == 0)
		{
			i = 0;
			j++;
		}
		free(c);
		free(r);
	}
}
