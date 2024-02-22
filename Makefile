# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 12:42:23 by cdumais           #+#    #+#              #
#    Updated: 2024/02/22 17:43:29 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
AUTHOR		:= cdumais
NAME		:= colorgame

CFG_DIR		:= cfg
IMG_DIR		:= img
INC_DIR		:= inc
LIB_DIR		:= lib
OBJ_DIR		:= obj
SRC_DIR		:= src
TMP_DIR		:= tmp

COMPILE		:= gcc
C_FLAGS		:= -Wall -Wextra -Werror
L_FLAGS		:= 
HEADERS		:= -I$(INC_DIR)

REMOVE		:= rm -rf
NPD			:= --no-print-directory
VOID		:= /dev/null
OS			:= $(shell uname)
# **************************************************************************** #
# ---------------------------------- LIBFT ----------------------------------- #
# **************************************************************************** #
LIBFT_DIR	:= $(LIB_DIR)/libft
LIBFT_INC	:= $(LIBFT_DIR)/$(INC_DIR)
LIBFT		:= $(LIBFT_DIR)/libft.a
HEADERS		:= $(HEADERS) -I$(LIBFT_INC)
# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
MLX_DIR		:= $(LIB_DIR)/MLX42
MLX_INC		:= $(MLX_DIR)/include/MLX42
MLX_BLD		:= $(MLX_DIR)/build
MLX42		:= $(MLX_BLD)/libmlx42.a

C_FLAGS		:= $(C_FLAGS) -Wunreachable-code -Ofast
L_FLAGS		:= $(L_FLAGS) -L$(MLX_BLD) -lmlx42
HEADERS		:= $(HEADERS) -I$(MLX_INC)
# **************************************************************************** #
# ---------------------------------- CONFIG  --------------------------------- #
# **************************************************************************** #
include $(CFG_DIR)/leaks.mk

SOUND		:=

ifeq ($(OS),Linux)
include $(CFG_DIR)/config_linux.mk
else ifeq ($(OS),Darwin)
include $(CFG_DIR)/config_mac.mk
else
$(error Unsupported operating system: $(OS))
endif

C_FLAGS		+= -DWIDTH=$(SCREEN_W) -DHEIGHT=$(SCREEN_H)
# **************************************************************************** #
# -------------------------------- SUBMODULES  ------------------------------- #
# **************************************************************************** #
INIT_CHECK	:= $(LIB_DIR)/.init_check
INIT		:= $(if $(wildcard $(INIT_CHECK)),,init_submodules)
# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
# INC		:= 
# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
# SRC		:=	
# **************************************************************************** #
# -------------------------------- ALL FILES --------------------------------- #
# **************************************************************************** #
# INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
# SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
# OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# -------------------------------- ALL * FILES ------------------------------- #
# **************************************************************************** #
INCS	:=	$(wildcard $(INC_DIR)/*.h)
SRCS	:=	$(wildcard $(SRC_DIR)/*.c)
OBJS	:=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(INIT) $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJS) $(INCS)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@
	@echo "$$TITLE"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) $(NPD)

$(MLX42):
	@echo "Building MLX42..."
	@cmake -S lib/MLX42 -B lib/MLX42/build -Wno-dev
	@echo "Compiling MLX42..."
	@$(MAKE) -C lib/MLX42/build -j4 $(NPD)
	@echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
	$(GREEN)\tbuilt successfully$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(REMOVE) $(OBJ_DIR); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Object files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No object files to remove$(RESET)"; \
	fi
	@$(MAKE) clean -C $(LIBFT_DIR) $(NPD)

fclean: clean
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Executable removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No executable to remove$(RESET)"; \
	fi

re: fclean all

bonus:
	@echo "feature not yet implemented..."

.PHONY: all clean fclean re bonus
# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
mlxclean:
	@if [ -f $(MLX42) ]; then \
		$(REMOVE) $(MLX_BLD); \
		echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
		$(GREEN)Library removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
		$(YELLOW)No library to remove$(RESET)"; \
	fi

mlxref:
	@$(OPEN) "https://github.com/codam-coding-college/MLX42/tree/master/docs"

tuto:
	@$(OPEN) "https://pulgamecanica.herokuapp.com/posts/mlx42-intro"

.PHONY: mlxclean mlxref tuto
# **************************************************************************** #
# ----------------------------------- GIT ------------------------------------ #
# **************************************************************************** #
init_submodules: $(INIT_CHECK)

WHEN	:= $(shell date "+On day %d of month %m in the year %Y at %H:%M and %S seconds")

$(INIT_CHECK):
	@git submodule update --init --recursive
	@echo "$(NAME)\n\
	by $(AUTHOR)\n\
	Compiled for $(USER)\n\
	$(WHEN)\n\
	$(MACHINE)" > $@

MAIN_BRANCH	:= $(shell git branch -r \
| grep -E 'origin/(main|master)' \
| grep -v 'HEAD' | head -n 1 | sed 's@^.*origin/@@')

update:
	@echo "Are you sure you want to update the repo and submodules? [y/N] " \
	&& read ANSWER; \
	if [ "$$ANSWER" = "y" ] || [ "$$ANSWER" = "Y" ]; then \
		echo "Updating repository from branch $(CYAN)$(MAIN_BRANCH)$(RESET)..."; \
		git pull origin $(MAIN_BRANCH); \
		$(MAKE) init_submodules; \
		echo "Repository updated."; \
	else \
		echo "Canceling update..."; \
	fi

.PHONY: init_submodules update
# **************************************************************************** #
# ---------------------------------- NORME ----------------------------------- #
# **************************************************************************** #
norm:
	@if which norminette > $(VOID); then \
		echo "$(BOLD)$(YELLOW)Norminetting $(PURPLE)$(NAME)$(RESET)"; \
		norminette -o $(INCS); \
		norminette -o $(SRCS); \
		$(MAKE) norm -C $(LIBFT_DIR); \
	else \
		echo "$(BOLD)$(YELLOW)Norminette not installed$(RESET)"; \
	fi

nm: $(NAME)
	@echo "$(BOLD)$(YELLOW)Functions in $(PURPLE)$(UNDERLINE)$(NAME)$(RESET):"
	@nm $(NAME) | grep U | grep -v 'ft_' \
				| sed 's/U//g' | sed 's/__//g' | sed 's/ //g' \
				| sort | uniq
	@$(MAKE) nm -C $(LIBFT_DIR) $(NPD)

.PHONY: norm nm
# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
PDF		:= cub3d_en.pdf
GIT_URL	:= https://github.com/SaydRomey/42_ressources
PDF_URL	:= $(GIT_URL)/blob/main/pdf/$(PDF)?raw=true

pdf: | $(TMP_DIR)
	@if [ -f $(TMP_DIR)/$(PDF) ]; then \
		echo "Opening $(PDF)..."; \
	else \
		echo "Downloading $(PDF)..."; \
		curl -# -L $(PDF_URL) -o $(TMP_DIR)/$(PDF); \
	fi
	@$(OPEN) $(TMP_DIR)/$(PDF)

.PHONY: pdf
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
run: all
	./$(NAME) $(MAP)

FORCE_FLAGS	:= -Wno-unused-variable

force: C_FLAGS += $(FORCE_FLAGS)
force: re
	@echo "adding flags $(YELLOW)$(FORCE_FLAGS)$(RESET)"
	@echo "$(RED)Forced compilation$(RESET)"

$(TMP_DIR):
	@mkdir -p $(TMP_DIR)
# **************************************************************************** #
ffclean: fclean vclean mlxclean
	@$(MAKE) fclean -C $(LIBFT_DIR) $(NPD)
	@$(REMOVE) $(TMP_DIR) $(INIT_CHECK) $(NAME).dSYM

.PHONY: run force ffclean
# **************************************************************************** #
# ---------------------------------- BACKUP (zip) ---------------------------- #
# **************************************************************************** #
USER		:=$(shell whoami)
ROOT_DIR	:=$(notdir $(shell pwd))
TIMESTAMP	:=$(shell date "+%Y%m%d_%H%M%S")
BACKUP_NAME	:=$(ROOT_DIR)_$(USER)_$(TIMESTAMP).zip
MOVE_TO		:= ~/Desktop/$(BACKUP_NAME)

zip: ffclean
	@if which zip > $(VOID); then \
		zip -r --quiet $(BACKUP_NAME) ./*; \
		mv $(BACKUP_NAME) $(MOVE_TO); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		compressed as: $(CYAN)$(UNDERLINE)$(MOVE_TO)$(RESET)"; \
	else \
		echo "Please install zip to use the backup feature"; \
	fi

.PHONY: zip
# **************************************************************************** #
# ------------------------------------ MAN ----------------------------------- #
# **************************************************************************** #
define MAN

Available 'make' targets:

'make [all]'   -> Compiles $(NAME) and necessary dependencies (libft and MLX42)
'make clean'   -> Removes the $(OBJ_DIR)/ directory and other object files
'make fclean'  -> Removes $(NAME) and $(LIBFT)
'make re'      -> Same as fclean and all
'make update'  -> Pulls the github version
'make norm'    -> Runs 'norminette' on the files in $(SRC_DIR)/ and $(INC_DIR)/ (also in libft)
'make nm'      -> Checks symbols in the executable (to check used functions)
'make pdf'     -> Downloads/Opens a $(NAME) instruction pdf in $(TMP_DIR)/
'make mlxref'  -> Opens the MLX42 documentation
'make tuto'    -> Opens the tutorial by $(PURPLE)pulgamecanica$(RESET)
'make leaks'   -> (WIP) Runs Valgrind on $(NAME) $(MAP) (make supp and make suppleaks)
'make run'     -> Same as 'make all', then './$(NAME) $(MAP)'
'make debug'   -> (WIP) Recompiles with debug symbols
'make force'   -> Recompiles with $(YELLOW)$(FORCE_FLAGS)$(RESET) (for testing)
'make ffclean' -> Removes files and directories created by this makefile
'make zip'     -> Creates a compressed version of this project on the desktop
'make info'    -> Prints compilation information
'make title'   -> Prints an example version of the title
'make spin'    -> (WIP) Animation that waits for a process to finish
'make sound'   -> (WIP) Plays a .wav sound
'make man'     -> Shows this message

endef
export MAN

man:
	@echo "$$MAN"

.PHONY: man
# **************************************************************************** #
# ----------------------------------- INFO ----------------------------------- #
# **************************************************************************** #
define INFO

$(NAME)
by $(AUTHOR)


$(UNDERLINE)Compiler$(RESET)
$(COMPILE)

$(UNDERLINE)C_FLAGS$(RESET)
 $(C_FLAGS)

$(UNDERLINE)I_FLAGS$(RESET)
$(HEADERS)

$(UNDERLINE)L_FLAGS$(RESET)
$(L_FLAGS)

$(UNDERLINE)Header files$(RESET)
$(INCS)

$(UNDERLINE)Source code$(RESET)
$(SRCS)

$(UNDERLINE)Libraries$(RESET)
$(LIBFT) $(MLX42)

$(UNDERLINE)Screen resolution$(RESET)
Width: $(SCREEN_W)
Height:$(SCREEN_H)

endef
export INFO

info:
	@echo "$$INFO"

.PHONY: info
# **************************************************************************** #
# ----------------------------------- DECO ----------------------------------- #
# **************************************************************************** # 
define TITLE
[$(BOLD)$(PURPLE)$@$(RESET)]\t\t$(GREEN)ready$(RESET)
$(ORANGE)
***************
* PLACEHOLDER *
***************
$(RESET)

type 'make run' to execute
or   'make man' for more options

endef
export TITLE

USER		:=$(shell whoami)
TIME		:=$(shell date "+%H:%M:%S")

title:
	@echo "$$TITLE"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"

.PHONY: title
# **************************************************************************** #
# ----------------------------------- ANSI ----------------------------------- #
# **************************************************************************** #
ESC			:= \033

RESET		:= $(ESC)[0m
BOLD		:= $(ESC)[1m
ITALIC		:= $(ESC)[3m
UNDERLINE	:= $(ESC)[4m

# Cursor movement
UP			:= $(ESC)[A
DOWN		:= $(ESC)[B
TOP_LEFT	:= $(ESC)[1;1H

# Erasing
ERASE_REST	:= $(ESC)[K
ERASE_LINE	:= $(ESC)[2K
ERASE_ALL	:= $(ESC)[2J

# Text color
BLACK		:= $(ESC)[30m
RED			:= $(ESC)[91m
GREEN		:= $(ESC)[32m
YELLOW		:= $(ESC)[93m
ORANGE		:= $(ESC)[38;5;208m
BLUE		:= $(ESC)[94m
PURPLE		:= $(ESC)[95m
CYAN		:= $(ESC)[96m
WHITE		:= $(ESC)[37m
GRAY		:= $(ESC)[90m

# Background
BG_BLACK	:= $(ESC)[40m
BG_RED		:= $(ESC)[101m
BG_GREEN	:= $(ESC)[102m
BG_YELLOW	:= $(ESC)[103m
BG_ORANGE	:= $(ESC)[48;5;208m
BG_BLUE		:= $(ESC)[104m
BG_PURPLE	:= $(ESC)[105m
BG_CYAN		:= $(ESC)[106m
BG_WHITE	:= $(ESC)[47m
BG_GRAY		:= $(ESC)[100m

# compilation example without makefile and flags
# gcc -fsanitize=address src/image_utils.c src/animate.c src/main.c -ldl -L/Users/cdumais/.brew/opt/glfw/lib -lglfw -lm -lpthread -Llib/MLX42/build -lmlx42 -Llib/libft/ -lft -Ilib/MLX42/include/MLX42 -Ilib/libft/inc -Iinc
