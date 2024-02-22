# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config_linux.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 17:11:21 by cdumais           #+#    #+#              #
#    Updated: 2024/02/22 12:57:55 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- Linux ------------------------------------ #
# **************************************************************************** #
# TODO: define default width and hight here
# 
C_FLAGS		+= -DOS_LINUX

GLFW_DIR 	:= $(shell ldconfig -p | grep libglfw | awk '{print $$4}' | xargs dirname | uniq)
GLFW		:= $(shell pkg-config --libs glfw3)

LIBS		:= -ldl -lm -pthread

L_FLAGS		:= $(L_FLAGS) -L$(GLFW_DIR) $(GLFW) $(LIBS)

OPEN		:= xdg-open
MACHINE		:= $(shell uname -a)
SOUND		:= aplay

# need to adapt this
DEFAULT_W	:= 500
DEFAULT_H	:= 500

XRANDR		:= xrandr | grep '*' | awk '{print $$1}'
SCREEN_W	:= $(shell $(XRANDR) | awk -Fx '{print $$1}' | head -n 1 || echo $(DEFAULT_W))
SCREEN_H	:= $(shell $(XRANDR) | awk -Fx '{print $$2}' | head -n 1 || echo $(DEFAULT_H))

# Dependencies

# Cmake
# GLFW


# # this also works but i wanted to test stuff...
# GLFW		:= -glfw
# L_FLAGS		:= $(L_FLAGS) $(GLFW) $(LIBS)

# for the second monitor.. (gets the second line)
# SCREEN_W	:= $(shell $(XRANDR) | awk -Fx '{print $$1}' | head -n 2 | tail -n 1 || echo $(DEFAULT_W))
