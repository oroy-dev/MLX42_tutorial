# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config_mac.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 17:11:25 by cdumais           #+#    #+#              #
#    Updated: 2024/02/22 12:57:32 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- MacOS ------------------------------------ #
# **************************************************************************** #
# TOCHECK: does using osascript create a problem on other 42 stations?
# 
C_FLAGS		+= -DOS_MAC

GLFW_DIR	:= $(shell brew --prefix glfw)/lib
GLFW		:= -lglfw

FRAMEWORKS	:= -framework Cocoa -framework OpenGL -framework IOKit

L_FLAGS		:= $(L_FLAGS) -L$(GLFW_DIR) $(GLFW) $(FRAMEWORKS)

OPEN		:= open
MACHINE		:= $(shell uname -a)
SOUND		:= afplay

# need to adapt this
DEFAULT_W	:= 500
DEFAULT_H	:= 500

OSA_SCREEN	:= osascript -e 'tell application "Finder" to get bounds of window of desktop'
SCREEN_W	:= $(shell $(OSA_SCREEN) | awk '{gsub(/,/, "", $$3); print $$3}' || echo $(DEFAULT_W))
SCREEN_H	:= $(shell $(OSA_SCREEN) | awk '{gsub(/,/, "", $$4); print $$4}' || echo $(DEFAULT_H))


# Dependencies

# HOMEBREW
# CMAKE
# GLFW


# # ideas to test
# GLFW_EXISTS	:= $(shell test -e $(GLFW_DIR)/libglfw.dylib && echo 1 || echo 0)
# GLFW		:= $(if $(filter $(GLFW_EXISTS),1),-lglfw, $(error GLFW library not found.)) #but install it instead ?

# GLFW_LIB_PATH=$(brew --prefix glfw)/lib
# if [ -e "$GLFW_LIB_PATH/libglfw.dylib" ]; then
# 	echo "-lglfw"
# else
# 	echo "GLFW library not found."
# fi
