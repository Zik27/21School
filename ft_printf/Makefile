# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/05 16:29:34 by djast             #+#    #+#              #
#    Updated: 2019/01/31 19:27:04 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
NAME_LIBFT = ./libft/libft.a
LIBS = 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
 
all: $(NAME)
 
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS += $(patsubst ./libft/%.c, ./libft/%.o, $(wildcard ./libft/*.c))
HEADERS = $(wildcard *.h)
 
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(AR) rc $(NAME) $(OBJECTS)

clean:
	@/bin/rm -rf $(OBJECTS)

fclean: clean
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(NAME_LIBFT)

re: fclean all