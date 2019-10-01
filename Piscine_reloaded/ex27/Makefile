# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/06 13:20:00 by vurrigon          #+#    #+#              #
#    Updated: 2018/11/23 10:53:43 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file

FLAGS = -Wall -Wextra -Werror

SRCS = ft_display_file.c ft_putstr.c

OB_FILES = ft_display_file.o ft_putstr.o

all: $(NAME)

clean:
	/bin/rm -f $(OB_FILES)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

$(NAME): $(OB_FILES)
	gcc -o $(NAME) $(OB_FILES)

ft_display_file.o:
	gcc $(FLAGS) -c ft_display_file.c

ft_putstr.o:
	gcc $(FLAGS) -c ft_putstr.c
