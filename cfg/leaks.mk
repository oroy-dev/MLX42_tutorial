# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    leaks.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:52:24 by cdumais           #+#    #+#              #
#    Updated: 2024/02/22 12:53:37 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# TODO: fix debug target to recompile mlx42 correctly (check documentation)
# 
debug: C_FLAGS += -g
debug: re

.PHONY: debug
# **************************************************************************** #
# -------------------------------- LEAKS ------------------------------------- #
# **************************************************************************** #
# TODO: check if we should put messages as an echo instead of a target
# TODO: maybe put this in a 'utils.mk' ?
# 
VAL_CHECK	:= $(shell which valgrind > $(VOID); echo $$?)

# valgrind options
ORIGIN		:= --track-origins=yes
LEAK_CHECK	:= --leak-check=full
LEAK_KIND	:= --show-leak-kinds=all

# valgrind additional options
CHILDREN	:= --trace-children=yes
FD_TRACK	:= --track-fds=yes
HELGRIND	:= --tool=helgrind
NO_REACH	:= --show-reachable=no
VERBOSE		:= --verbose
VAL_LOG		:= valgrind-out.txt
LOG_FILE	:= --log-file=$(VAL_LOG)

# suppression-related options
SUPP_FILE	:= suppression.supp
SUPP_GEN	:= --gen-suppressions=all
SUPPRESS	:= --suppressions=$(SUPP_FILE)

# default valgrind tool
BASE_TOOL	= valgrind $(ORIGIN) $(LEAK_CHECK) $(LEAK_KIND)
# **************************************************************************** # Choose valgrind options here
# specific valgrind tool (add 'additional options' variables as needed)
# 
BASE_TOOL	+= 
# 
# **************************************************************************** #
LEAK_TOOL	= $(BASE_TOOL) $(LOG_FILE)
SUPP_TOOL	= $(BASE_TOOL) $(SUPP_GEN) $(LOG_FILE)

# run valgrind
leaks_msg:
	@echo "[$(BOLD)$(PURPLE)valgrind$(RESET)] \
	$(ORANGE)\tRecompiling with debug flags$(RESET)"

leaks: leaks_msg debug
	@if [ $(VAL_CHECK) -eq 0 ]; then \
		echo "[$(BOLD)$(PURPLE)valgrind$(RESET)] \
		$(ORANGE)Launching valgrind\n$(RESET)#"; \
		$(LEAK_TOOL) ./$(NAME) $(ARGS); \
		echo "#\n[$(BOLD)$(PURPLE)valgrind$(RESET)] \
		$(ORANGE)info in: $(CYAN)$(VAL_LOG)$(RESET)"; \
	else \
		echo "Please install valgrind to use the 'leaks' feature"; \
	fi

# generate suppression file
supp_msg:
	@echo "generating suppression file"
supp: leaks_msg supp_msg debug
	$(SUPP_TOOL) ./$(NAME) $(ARGS) && \
	awk '/^{/,/^}/' valgrind-out.txt > suppression.supp

# use suppression file
suppleaks_msg:
	@echo "launching valgrind with suppression file"
suppleaks: debug
	$(LEAK_TOOL) $(SUPPRESS) ./$(NAME) $(ARGS)

# remove suppression and log files
vclean:
	@if [ -n "$(wildcard suppression.supp)" ]; then \
		$(REMOVE) $(SUPP_FILE); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)suppression file removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)no suppression file to remove$(RESET)"; \
	fi
	@if [ -n "$(wildcard valgrind-out.txt)" ]; then \
		$(REMOVE) valgrind-out.txt; \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)log file removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)no log file to remove$(RESET)"; \
	fi

.PHONY: leaks_msg leaks supp_msg supp suppleaks_msg suppleaks vclean
