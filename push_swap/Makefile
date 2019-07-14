# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/28 15:07:54 by vurrigon          #+#    #+#              #
#    Updated: 2019/07/14 16:51:32 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_PS = push_swap
NAME_CHECK = checker
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = list.c op_rotate.c op_swap_push.c reader.c sorting_below_four.c \
		sorting_below_six.c utils.c valid.c push_swap.c checker.c
SRC_LIB = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
		ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
		ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
		ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
		ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
		ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
		ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c get_next_line.c
SRCS += $(addprefix ./libft/, $(SRC_LIB))
OBJECTS =  ${SRCS:.c=.o}
OBJECTS_PS := $(filter-out checker.o,$(OBJECTS))
OBJECTS_CHECK := $(filter-out push_swap.o,$(OBJECTS))

all: $(NAME_PS) $(NAME_CHECK)

$(NAME_CHECK):
	$(CC) $(OBJECTS_CHECK) ./libft/*.o -o $(NAME_CHECK)

$(NAME_PS): $(OBJECTS)
	$(CC) $(OBJECTS_PS) ./libft/*.o -o $(NAME_PS) 

$(OBJECTS):
	$(CC) -c $(SRCS)
	@echo $(OBJECTS)

clean:
	/bin/rm -rf $(OBJECTS)

fclean: clean
	/bin/rm -rf $(NAME_CHECK) $(NAME_PS)

re: fclean all

