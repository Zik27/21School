/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 13:37:36 by djast             #+#    #+#             */
/*   Updated: 2019/11/29 17:17:49 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void			draw_map_symbol(t_sdl *sdl, char text, SDL_Rect r, SDL_Color color)
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

void	draw_text(t_sdl *sdl, char *text, SDL_Rect button, SDL_Color color)
{
	sdl->surface = TTF_RenderText_Solid(sdl->font, text, color);
	SDL_DestroyTexture(sdl->text);
	sdl->text = SDL_CreateTextureFromSurface(sdl->renderer,
											sdl->surface);
	SDL_FreeSurface(sdl->surface);
	SDL_RenderCopy(sdl->renderer, sdl->text, NULL, &button);
}


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

void draw_text_on_right_panel(t_sdl *sdl, t_vm_info *info)
{
	SDL_Rect *r;
	SDL_Color *c;
	char *text;

	r = create_sdl_rect(COREWAR_TEXT_X, COREWAR_TEXT_Y,
							COREWAR_TEXT_SIZE_X, COREWAR_TEXT_SIZE_Y);
	c = create_sdl_color(255, 255, 255, 0);
	draw_text(sdl, "Welcome to COREWAR!", *r, *c);
	free(r);

	r = create_sdl_rect(SPEED_TEXT_X, SPEED_TEXT_Y,
							SPEED_TEXT_SIZE_X, SPEED_TEXT_SIZE_Y);
	draw_text(sdl, "Speed: ", *r, *c);
	free(r);

	r = create_sdl_rect(SPEED_RES_X, SPEED_RES_Y,
							SPEED_RES_SIZE_X, SPEED_RES_SIZE_Y);
	text = ft_itoa(sdl->speed);
	draw_text(sdl, text, *r, *c);
	free(text);
	free(r);

	r = create_sdl_rect(CYCLE_TEXT_X, CYCLE_TEXT_Y,
							CYCLE_TEXT_SIZE_X, CYCLE_TEXT_SIZE_Y);
	draw_text(sdl, "Cycle: ", *r, *c);
	free(r);

	r = create_sdl_rect(CYCLE_RES_X, CYCLE_RES_Y,
							CYCLE_RES_SIZE_X, CYCLE_RES_SIZE_Y);
	text = ft_itoa(info->cycle - 1);
	draw_text(sdl, text, *r, *c);
	free(r);




	free(c);
}


static void		draw_right_panel(t_sdl *sdl, t_vm_info *info)
{
	SDL_Rect	r;

	r.x = SIZE_WIN_X * 0.76;
	r.y = 0;
	r.w = SIZE_WIN_X * 0.24;
	r.h = SIZE_WIN_Y;
	SDL_SetRenderDrawColor(sdl->renderer, 24, 24, 24, 0);
	SDL_RenderFillRect(sdl->renderer, &r);
	
	draw_text_on_right_panel(sdl, info);
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
	draw_right_panel(sdl, info);
	
	draw_carriages(sdl, info);
	draw_map(sdl, info);
	

	SDL_RenderPresent(sdl->renderer);
}