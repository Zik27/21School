/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_right_panel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 13:15:09 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 15:58:18 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			draw_cycle_text(t_sdl *sdl, t_vm_info *info, SDL_Color *c)
{
	SDL_Rect	*r;
	char		*text;

	r = create_sdl_rect(CYCLE_TEXT_X, CYCLE_TEXT_Y,
							CYCLE_TEXT_SIZE_X, CYCLE_TEXT_SIZE_Y);
	draw_text(sdl, "Cycle: ", *r, *c);
	free(r);
	r = create_sdl_rect(CYCLE_RES_X, CYCLE_RES_Y,
							CYCLE_RES_SIZE_X, CYCLE_RES_SIZE_Y);
	text = ft_itoa(info->cycle - 1);
	draw_text(sdl, text, *r, *c);
	free(text);
	free(r);
	free(c);
}

void			draw_text_on_right_panel(t_sdl *sdl, t_vm_info *info)
{
	SDL_Rect	*r;
	SDL_Color	*c;
	char		*text;

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
	draw_cycle_text(sdl, info, c);
}

void			draw_right_panel(t_sdl *sdl, t_vm_info *info)
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
