# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 17:18:06 by djast             #+#    #+#              #
#    Updated: 2019/09/17 12:59:42 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM = asm

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_FOLDER = ./libft
LIBFT = $(LIBFT_FOLDER)/libft.a
LIBFT_HEADER = $(LIBFT_FOLDER)/libft.h


HEADERS_DIRECTORY = ./includes
HEADERS = $(HEADERS_DIRECTORY)/corewar.h

LIBS = -lft -L$(LIBFT_FOLDER)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_FOLDER)

COMMON_FILES =	asm.c \

SRC_DIRECTORY = ./srcs/
SRC_COMMON_FILES = $(addprefix $(SRC_DIRECTORY), $(COMMON_FILES))

OBJ_FILES_COMMON = $(patsubst %.c, %.o, $(COMMON_FILES))

OBJ_DIRECTORY = ./objects/
OBJ_COMMON_FILES = $(addprefix $(OBJ_DIRECTORY), $(OBJ_FILES_COMMON))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME_ASM)

$(NAME_ASM): $(LIBFT) $(OBJ_DIRECTORY) $(OBJ_COMMON_FILES)
	@$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) $(OBJ_COMMON_FILES)  -o $(NAME_ASM)
	@echo "$(RED)$(NAME_ASM) $(GREEN)compiled successfully!$(RESET)"

$(OBJ_DIRECTORY):
	@mkdir -p $(OBJ_DIRECTORY)

$(OBJ_DIRECTORY)%.o : $(SRC_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_FOLDER)
	@echo "$(RED)Libft $(GREEN)compiled successfully!$(RESET)"

clean:
	@$(MAKE) -sC $(LIBFT_FOLDER) clean
	@echo "$(RED)Libft $(GREEN)object files were deleted!$(RESET)"
	@/bin/rm -rf $(OBJ_COMMON_FILES)
	@echo "$(RED)Object $(GREEN)files deleted.$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_FOLDER) fclean
	@echo "$(RED)Libft.a $(GREEN)was deleted.$(RESET)"
	@/bin/rm -rf $(NAME_ASM)
	@echo "$(RED)$(NAME_ASM) $(GREEN)was deleted.$(RESET)"

re: fclean all
