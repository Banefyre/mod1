# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msagodir <msagodir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/06 10:13:32 by msagodir          #+#    #+#              #
#    Updated: 2015/02/03 17:52:35 by msagodir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash
UNAME = $(shell uname -s)
CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -Werror `pkg-config --cflags glfw3 glew` -I./includes -I ~/.brew/include
DEBUG = -g3 -fno-inline -DD_ERRORS_ON
OBJDIR  = .objs
LDFLAGS = `pkg-config --static --libs glfw3 glew`
LISTDIR = srcs
DIRSRC = srcs
NAME = mod1
SRC = $(wildcard $(DIRSRC)/*.cpp)
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

.SILENT:

$(addprefix $(OBJDIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
ifeq ($(UNAME), Darwin)
	printf '\033[0;32mBuilding C++ Object $@\n\033[0m' "Building C++ Object $@"
else
	echo -e '\033[0;32mBuilding C++ Object $@\n\033[0m' "Building C++ Object $@"
endif

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
ifeq ($(UNAME), Darwin)
	printf '\033[1;31m%s \033[1;35m%s \033[1;31m%s \033[1;33m%s\n\033[0m' \
		"Linking C++ executable" "$(NAME)" "with" "$(CC)"
else
	echo -e '\033[1;31m%s \033[1;35m%s \033[1;31m%s \033[1;33m%s\n\033[0m' \
		"Linking C++ executable" "$(NAME)" "with" "$(CC)"
endif

clean:
	/bin/rm -fr $(OBJDIR)
ifeq ($(UNAME), Darwin)
	printf '\033[1;34m%s\n\033[0m' "Clean project $(NAME)"
else
	echo -e '\033[1;34m%s\n\033[0m' "Clean project $(NAME)"
endif

test: CFLAGS = -Wall
test: re

debug: CFLAGS += $(DEBUG)
debug: re
ifeq ($(UNAME), Darwin)
	printf '\033[1;31m%s \033[1;35m%s\n\033[0m' "Debug version" "$(DEBUG)"
else
	echo -e '\033[1;31m%s \033[1;35m%s\n\033[0m' "Debug version" "$(DEBUG)"
endif

fclean: clean
	/bin/rm -fr $(NAME)
ifeq ($(UNAME), Darwin)
	printf '\033[1;34m%s\n\033[0m' "Fclean project $(NAME)"
else
	echo -e '\033[1;34m%s\n\033[0m' "Fclean project $(NAME)"
endif

re: fclean all

$(OBJDIR):
	/bin/mkdir $(OBJDIR);            \
	for DIR in $(LISTDIR);           \
	do                               \
		/bin/mkdir $(OBJDIR)/$$DIR;  \
	done                             \

.PHONY: clean fclean re
