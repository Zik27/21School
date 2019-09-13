/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:25:28 by djast             #+#    #+#             */
/*   Updated: 2019/09/11 19:41:13 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_sdl		*create_window(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	sdl->window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, SIZE_WINDOW_X, SIZE_WINDOW_Y,
					SDL_WINDOW_OPENGL);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
											SDL_RENDERER_ACCELERATED);
	sdl->Sans = TTF_OpenFont("OpenSans.ttf", 500);
	sdl->surface = SDL_LoadBMP("20483.bmp");
	sdl->background = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
	SDL_FreeSurface(sdl->surface);
	sdl->surface = SDL_LoadBMP("ant.bmp");
	sdl->ant = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
	SDL_FreeSurface(sdl->surface);
	SDL_SetWindowFullscreen(sdl->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	return (sdl);
}

void				put_text(t_sdl *sdl, char *message, SDL_Color color, t_room *cur_room)
{
	SDL_Rect	r;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sdl->Sans, message, color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(sdl->renderer, surfaceMessage);
	r.x = cur_room->x - ROOM_SIZE / 2;
	r.y = cur_room->y - ROOM_SIZE - 5;
	r.h = 2 * ROOM_SIZE / 3;
	r.w = ROOM_SIZE;
	SDL_RenderCopy(sdl->renderer, Message, NULL, &r);
}