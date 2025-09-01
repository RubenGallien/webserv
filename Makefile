# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 16:25:07 by lvicino           #+#    #+#              #
#    Updated: 2025/08/05 17:25:15 by lvicino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

BUILD_DIR	=	build




CONF_LIB	=	src/conf/conf.a
CONF_OBJ	:=	$(shell find src/conf -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \))
MAKE_CONF	=	make -C src/conf


SERVER_LIB	=	src/server/server.a
SERVER_OBJ	:=	$(shell find src/server -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \))
MAKE_SERVER	=	make -C src/server



SRC_DIR		=	src

MAIN		=	main.cpp

MAIN		:=	$(MAIN:%=$(SRC_DIR)/%)
MAIN_OBJ	=	$(MAIN:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MAIN_DEP	=	$(MAIN_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



CC			=	c++
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP -std=c++98
INCLUDE		=	-I src/conf/include \
				-I src/server/include \
				-I src/server/include/Utils \

MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)


all		:	$(NAME)

$(NAME)	:	$(MAIN_OBJ) $(CONF_LIB) $(SERVER_LIB)
	$(CC) $(MAIN_OBJ) $(CONF_LIB) $(SERVER_LIB) -o $(NAME)

$(BUILD_DIR)/%.o	:	$(SRC_DIR)/%.cpp
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(CONF_LIB)	:	$(CONF_OBJ)
	$(MAKE_CONF)

$(SERVER_LIB)	:	$(SERVER_OBJ)
	$(MAKE_SERVER)

-include $(MAIN_DEP)

clean	:
	if [ -d "$(BUILD_DIR)" ]; then \
		rm -rf $(BUILD_DIR); \
	fi
	make -C src/conf clean
	make -C src/server clean

fclean	:	clean
	if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi
	make -C src/conf fclean
	make -C src/server fclean
	rm -rf ./.vscode

re		:	fclean all

.PHONY	:	clean fclean re
.SILENT	:	clean fclean
