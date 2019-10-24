/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 13:37:36 by djast             #+#    #+#             */
/*   Updated: 2019/10/24 17:41:49 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

SDL_Color		*create_sdl_color(int r, int g, int b, int a)
{
	SDL_Color *color;

	color = (SDL_Color *)malloc(sizeof(SDL_Color));
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
	return (color);
}

SDL_Rect		*create_sdl_rect(int x, int y, int w, int h)
{
	SDL_Rect *r;

	r = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
	return (r);
}


static void		draw_right_panel(t_sdl *sdl)
{
	SDL_Rect	r;

	r.x = SIZE_WIN_X * 0.76;
	r.y = 0;
	r.w = SIZE_WIN_X * 0.24;
	r.h = SIZE_WIN_Y;
	SDL_SetRenderDrawColor(sdl->renderer, 24, 24, 24, 0);
	SDL_RenderFillRect(sdl->renderer, &r);
}

void			draw_text(t_sdl *sdl, char text, SDL_Rect r, SDL_Color color)
{
	char *data;
	
	data = ft_strnew(2);
	data[0] = (text & 0xFF) / 16 > 9 ? (text & 0xFF) / 16 + '7' : (text & 0xFF) / 16 + '0';
	data[1] = (text & 0xFF) % 16 > 9 ? (text & 0xFF) % 16 + '7' : (text & 0xFF) % 16 + '0';
	sdl->surface = TTF_RenderText_Solid(sdl->font, data, color);
	SDL_DestroyTexture(sdl->text);
	sdl->text = SDL_CreateTextureFromSurface(sdl->renderer,
													sdl->surface);
	SDL_FreeSurface(sdl->surface);
	SDL_RenderCopy(sdl->renderer, sdl->text, NULL, &r);
	free(data);
}

static void		draw_map(t_sdl *sdl, t_vm_info *info)
{
	int i;
	int j;
	SDL_Rect	*r;
	SDL_Color	*c;

	i = 0;
	j = 0;
	while (i + (j * 64) < MEM_SIZE)
	{
		if (info->color_map[i + j * 64] == 1)
			c = create_sdl_color(0, 0, 173, 0);
		else if (info->color_map[i + j * 64] == 2)
			c = create_sdl_color(173, 0, 0, 0);
		else if (info->color_map[i + j * 64] == 3)
			c = create_sdl_color(0, 173, 0, 0);
			
		else
			c = create_sdl_color(128, 128, 128, 0);
		r = create_sdl_rect(10 + i * (SYMBOL_SIZE + SPACE_SIZE), 10 + j * (SYMBOL_SIZE + SPACE_SIZE), SYMBOL_SIZE, SYMBOL_SIZE);
		draw_text(sdl, info->map[i + j * 64], *r, *c);
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

static void		draw_carriages(t_sdl *sdl, t_vm_info *info)
{
	(void) sdl;
	t_carriage *carr;
	SDL_Rect	*r;

	carr = info->carriages;
	while (carr != NULL)
	{
		r = create_sdl_rect(10 + carr->cur_pos % 64 * (SYMBOL_SIZE + SPACE_SIZE), 10 + carr->cur_pos / 64 * (SYMBOL_SIZE + SPACE_SIZE), SYMBOL_SIZE, SYMBOL_SIZE);
		if (info->color_map[carr->cur_pos] == 1)
			SDL_SetRenderDrawColor(sdl->renderer, 64, 64, 255, 0);
		else if (info->color_map[carr->cur_pos] == 2)
			SDL_SetRenderDrawColor(sdl->renderer, 255, 64, 64, 0);
		else if (info->color_map[carr->cur_pos] == 3)
			SDL_SetRenderDrawColor(sdl->renderer, 64, 255, 64, 0);
		else
			SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(sdl->renderer, r);
		carr = carr->next;
		free(r);
	}

}

void			draw(t_sdl *sdl, t_vm_info *info)
{
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl->renderer);

	draw_right_panel(sdl);
	draw_carriages(sdl, info);
	draw_map(sdl, info);
	

	SDL_RenderPresent(sdl->renderer);
}