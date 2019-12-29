/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 15:22:06 by djast             #+#    #+#             */
/*   Updated: 2019/12/29 15:38:02 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		make_sdl_step(t_champ *champs, t_vm_info *info, t_sdl *sdl, int *i)
{
	if (make_step_cycle(info, champs) == 1)
		return ;
	info->cycle++;
	info->cycles_after_check++;
	(*i)++;
	if (info->carriages == NULL)
	{
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		return ;
	}
}

void		check_key_press(t_vm_info *info, t_sdl *sdl)
{
	if (sdl->window_event.type == SDL_KEYDOWN && SDLK_r ==
				sdl->window_event.key.keysym.sym)
	{
		sdl->speed += 100;
		draw(sdl, info);
	}
	else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_e ==
				sdl->window_event.key.keysym.sym)
	{
		sdl->speed += 10;
		draw(sdl, info);
	}
	else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_w ==
				sdl->window_event.key.keysym.sym)
	{
		sdl->speed = sdl->speed > 9 ? sdl->speed - 10 : 0;
		draw(sdl, info);
	}
	else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_q ==
				sdl->window_event.key.keysym.sym)
	{
		sdl->speed = sdl->speed > 99 ? sdl->speed - 100 : 0;
		draw(sdl, info);
	}
}

void		sdl_loop(t_champ *champs, t_vm_info *info, t_sdl *sdl, int *i)
{
	while (*i < sdl->speed && sdl->is_pause == 0)
		make_sdl_step(champs, info, sdl, i);
	if (sdl->is_pause == 0)
		draw(sdl, info);
	if (SDL_PollEvent(&(sdl->window_event)))
	{
		if (SDL_QUIT == sdl->window_event.type)
			exit(0);
		else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_ESCAPE ==
					sdl->window_event.key.keysym.sym)
			exit(0);
		else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_SPACE ==
					sdl->window_event.key.keysym.sym)
			sdl->is_pause = !sdl->is_pause;
		else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_s ==
				sdl->window_event.key.keysym.sym && sdl->is_pause == 1)
		{
			make_sdl_step(champs, info, sdl, i);
			draw(sdl, info);
		}
		else
			check_key_press(info, sdl);
	}
}
