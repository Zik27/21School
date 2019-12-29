/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 13:37:36 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 13:15:17 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			draw_text(t_sdl *sdl, char *text, SDL_Rect button,
										SDL_Color color)
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

static void		draw_carriages(t_sdl *sdl, t_vm_info *info)
{
	t_carriage	*carr;
	SDL_Rect	*r;

	carr = info->carriages;
	while (carr != NULL)
	{
		r = create_sdl_rect(10 + carr->cur_pos % 64 * (SYMBOL_SIZE +
			SPACE_SIZE), 10 + carr->cur_pos / 64 * (SYMBOL_SIZE + SPACE_SIZE),
										SYMBOL_SIZE, SYMBOL_SIZE);
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
