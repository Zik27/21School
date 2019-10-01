# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 20:06:06 by vurrigon          #+#    #+#              #
#    Updated: 2018/11/20 20:48:17 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Werror -Wextra
HEADERS = ./includes/
SRCS = ./srcs/

all: $(NAME)

clean:
	/bin/rm -f ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

$(NAME): ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o
	ar rc $(NAME) ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o
	ranlib $(NAME)

ft_putchar.o:
	gcc -c $(FLAG) $(SRCS)ft_putchar.c -I $(HEADERS)

ft_putstr.o:
	gcc -c $(FLAG) $(SRCS)ft_putstr.c -I $(HEADERS)

ft_strcmp.o:
	gcc -c $(FLAG) $(SRCS)ft_strcmp.c -I $(HEADERS)

ft_strlen.o:
	gcc -c $(FLAG) $(SRCS)ft_strlen.c -I $(HEADERS)

ft_swap.o:
	gcc -c $(FLAG) $(SRCS)ft_swap.c -I $(HEADERS)
