# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/28 15:07:54 by vurrigon          #+#    #+#              #
#    Updated: 2019/07/26 15:31:44 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_PS = push_swap
NAME_CHECK = checker
CC = gcc
CFLAGS = -Wall -Wextra -Werror
PATH_LIB = ./libft/
SRCS = list.c op_rotate.c op_swap_push.c reader.c sorting_below_four.c \
		sorting_below_six.c utils.c valid.c sorting_more_six.c main_sorting.c\
		solver.c push_swap.c checker.c
OBJECTS =  ${SRCS:.c=.o}
OBJECTS_PS := $(filter-out checker.o,$(OBJECTS))
OBJECTS_CHECK := $(filter-out push_swap.o,$(OBJECTS))

all: $(NAME_PS) $(NAME_CHECK)


$(NAME_CHECK): $(OBJECTS_CHECK)
	$(CC) $(CFLAGS) $(OBJECTS_CHECK) -L$(PATH_LIB) -lft -L$(PATH_LIB) -lftprintf -o $(NAME_CHECK)

$(NAME_PS): $(OBJECTS_PS)
	$(CC) $(CFLAGS) $(OBJECTS_PS) -L$(PATH_LIB) -lft -L$(PATH_LIB) -lftprintf -o $(NAME_PS) 

$(OBJECTS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	$(MAKE) -C $(PATH_LIB)

clean:
	$(MAKE) clean -C $(PATH_LIB)
	/bin/rm -rf $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C $(PATH_LIB)
	/bin/rm -rf $(NAME_CHECK) $(NAME_PS)

re: fclean all

