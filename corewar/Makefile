# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djast <djast@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 17:18:06 by djast             #+#    #+#              #
#    Updated: 2019/10/16 15:29:40 by djast            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM = asm
NAME_COREWAR = corewar

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_FOLDER = ./libft
LIBFT = $(LIBFT_FOLDER)/libft.a
LIBFT_HEADER = $(LIBFT_FOLDER)/libft.h


HEADERS_DIRECTORY = ./includes
HEADERS = $(HEADERS_DIRECTORY)/corewar.h
HEADER_DASM = $(HEADERS_DIRECTORY)/dasm.h

LIBS = -lft -L$(LIBFT_FOLDER) -lftprintf -L$(LIBFT_FOLDER)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_FOLDER)

FILES_ASM =		asm.c \
				error.c \
				utils.c \
				dasm.c \
				handle_args.c \
				handle_commands.c \
				init_dasm.c \
				valid.c \
				write_to_file.c \
				utils_dasm.c \
				free_dasm.c

FILSE_COREWAR = corewar.c \
				parse.c \
				print.c \
				check.c \
				init.c \
				get_champ.c \
				utils.c \
				put_players.c \
				carriage.c \
				op_add_sub.c \
				op_aff.c \
				op_and_or_xor.c \
				op_fork_lfork.c \
				op_ld_ldi_lld_lldi.c \
				op_live.c \
				op_st_sti.c\
				op_utils.c \
				op_zjmp.c \
				free.c

SRC_DIRECTORY = ./srcs/
SRC_DIRECTORY_ASM = $(SRC_DIRECTORY)asm/
SRC_DIRECTORY_COREWAR = $(SRC_DIRECTORY)corewar/

SRC_FILES_ASM = $(addprefix $(SRC_DIRECTORY_ASM), $(FILES_ASM))
SRC_FILES_COREWAR = $(addprefix $(SRC_DIRECTORY_COREWAR), $(FILSE_COREWAR))

OBJ_FILES_ASM = $(patsubst %.c, %.o, $(FILES_ASM))
OBJ_FILES_COREWAR = $(patsubst %.c, %.o, $(FILSE_COREWAR))

OBJ_DIRECTORY = ./objects/
OBJ_DIRECTORY_ASM = $(OBJ_DIRECTORY)asm/
OBJ_DIRECTORY_COREWAR = $(OBJ_DIRECTORY)corewar/

OBJ_ASM_FILES = $(addprefix $(OBJ_DIRECTORY_ASM), $(OBJ_FILES_ASM))
OBJ_COREWAR_FILES = $(addprefix $(OBJ_DIRECTORY_COREWAR), $(OBJ_FILES_COREWAR))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME_ASM) $(NAME_COREWAR)

$(NAME_ASM): $(LIBFT) $(OBJ_DIRECTORY) $(OBJ_DIRECTORY_ASM) $(OBJ_ASM_FILES) $(HEADER_DASM)
	@$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) $(OBJ_ASM_FILES)  -o $(NAME_ASM)
	@echo "$(RED)$(NAME_ASM) $(GREEN)compiled successfully!$(RESET)"

$(NAME_COREWAR): $(LIBFT) $(OBJ_DIRECTORY) $(OBJ_DIRECTORY_COREWAR) $(OBJ_COREWAR_FILES)
	@$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) $(OBJ_COREWAR_FILES)  -o $(NAME_COREWAR)
	@echo "$(RED)$(NAME_COREWAR) $(GREEN)compiled successfully!$(RESET)"

$(OBJ_DIRECTORY):
	@mkdir -p $(OBJ_DIRECTORY)

$(OBJ_DIRECTORY_ASM):
	@mkdir -p $(OBJ_DIRECTORY_ASM)

$(OBJ_DIRECTORY_COREWAR):
	@mkdir -p $(OBJ_DIRECTORY_COREWAR)

$(OBJ_DIRECTORY_ASM)%.o : $(SRC_DIRECTORY_ASM)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJ_DIRECTORY_COREWAR)%.o : $(SRC_DIRECTORY_COREWAR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_FOLDER)
	@echo "$(RED)Libft $(GREEN)compiled successfully!$(RESET)"

clean:
	@$(MAKE) -sC $(LIBFT_FOLDER) clean
	@echo "$(RED)Libft $(GREEN)object files were deleted!$(RESET)"
	@/bin/rm -rf $(OBJ_ASM_FILES)
	@/bin/rm -rf $(OBJ_COREWAR_FILES)
	@echo "$(RED)Object $(GREEN)files deleted.$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_FOLDER) fclean
	@echo "$(RED)Libft.a $(GREEN)was deleted.$(RESET)"
	@/bin/rm -rf $(NAME_COREWAR)
	@/bin/rm -rf $(NAME_ASM)
	@echo "$(RED)$(NAME_ASM) $(GREEN)was deleted.$(RESET)"

re: fclean all
