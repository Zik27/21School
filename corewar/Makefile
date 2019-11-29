# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 17:18:06 by djast             #+#    #+#              #
#    Updated: 2019/11/29 13:23:11 by vurrigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM = asm
NAME_COREWAR = corewar

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O3

LIBFT_FOLDER = ./libft
LIBFT = $(LIBFT_FOLDER)/libft.a
LIBFT_HEADER = $(LIBFT_FOLDER)/libft.h


HEADERS_DIRECTORY = ./includes
HEADERS = $(HEADERS_DIRECTORY)/corewar.h
HEADER_DASM = $(HEADERS_DIRECTORY)/dasm.h

ID_UN := $(shell id -un)

SDL_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/include/SDL2
SDL_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/lib

SDL_TTF_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2
SDL_TTF_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/lib

LIBS = -lft -L$(LIBFT_FOLDER) -L$(SDL_TTF_LIB) -L$(SDL_LIB) -lftprintf -L$(LIBFT_FOLDER) -lSDL2 -lSDL2_ttf
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_FOLDER) -I$(SDL_TTF_FOLDER) -I$(SDL_FOLDER)

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
				free_dasm.c \
				bytecode.c \
				bytecode_translate.c \
				free_asm.c \
				ft_split_spaces.c \
				init.c \
				instructions_arguments.c \
				instructions.c \
				is_something_check.c \
				lable_handle.c \
				parse_body.c \
				parse_name_comment_check_error.c \
				parse_name_comment_check.c \
				parse_name_comment.c \
				tokenize.c \
				valid_arg_type.c \
				valid_arguments.c \


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
				free.c \
				draw.c

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

all: install_sdl $(NAME_ASM) $(NAME_COREWAR)

no_sdl: $(NAME_ASM) $(NAME_COREWAR)

install_sdl:
	@brew install sdl2
	@brew switch sdl2 2.0.10
	@brew install sdl2_ttf
	@brew switch sdl2_ttf 2.0.15
	@brew install sdl2_mixer
	@brew switch sdl2_mixer 2.0.4

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
