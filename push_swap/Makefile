# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/28 15:07:54 by vurrigon          #+#    #+#              #
#    Updated: 2019/03/28 15:15:04 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS += $(patsubst ./ft_printf/%.c, ./ft_printf/%.o, $(wildcard ./ft_printf/*.c))
OBJECTS += $(patsubst ./libft/%.c, ./libft/%.o, $(wildcard ./libft/*.c))
HEADERS = $(wildcard *.h)

all: $(NAME)
 
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(NAME) -g

clean:
	@/bin/rm -rf $(OBJECTS)

fclean: clean
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(NAME_LIBFT)

re: fclean all

