# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djast <djast@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 17:18:06 by djast             #+#    #+#              #
#    Updated: 2019/03/07 12:11:03 by djast            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
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
