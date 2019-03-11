# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 17:00:22 by jfourne           #+#    #+#              #
#    Updated: 2019/03/07 11:23:41 by jfourne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	expert_system

SRC_PATH	=	src

SRC_NAME	=	Creator.class.cpp \
				Lexer.class.cpp \
				Parser.class.cpp \
				Tree.class.cpp \
				TreeBrowser.class.cpp \
				main.cpp \

OBJ_PATH	=	obj

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++

CPPFLAGS	=	-Iinclude

CFLAGS		=	-Wall -Wextra -Werror

OBJ_NAME	=	$(SRC_NAME:.cpp=.o)

SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all		: $(NAME)


$(NAME):		$(OBJ)
				@$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $@
				@echo "compilation completed"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
				@rm -rf $(OBJ)
				@rm -rf $(OBJ_PATH)
				@echo "rm OBJ"

fclean:			clean
				@rm -rf $(NAME)
				@echo "rm NAME"

re:				fclean all

.PHONY	: all clean fclean re
