# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djast <djast@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/05 16:29:34 by djast             #+#    #+#              #
#    Updated: 2019/01/05 20:20:53 by djast            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIBS = 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
 
all: $(NAME)
 
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS += $(patsubst ./libft/%.c, ./libft/%.o, $(wildcard ./libft/*.c))
HEADERS = $(wildcard *.h)
 
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) -Wall -o $@

clean:
	@/bin/rm -rf $(OBJECTS)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all