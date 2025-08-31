# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 16:25:07 by lvicino           #+#    #+#              #
#    Updated: 2025/08/05 17:25:30 by lvicino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	conf.a

BUILD_DIR	=	build



SRC_DIR		=	src

SRC			=	ServerConf.cpp \
				Conf.cpp \
				ErrorPath.cpp

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
SRC_OBJ		=	$(SRC:%.cpp=$(BUILD_DIR)/%.o)
SRC_DEP		=	$(SRC_OBJ:%.o=%.d)



CC			=	c++
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP -std=c++98
INCLUDE		=	-I include

MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)


all		:	$(NAME)

$(NAME)	:	$(SRC_OBJ)
	ar rcs $(NAME) $(SRC_OBJ)

$(BUILD_DIR)/%.o	:	%.cpp
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

-include $(SRC_DEP)

clean	:
	if [ -d "$(BUILD_DIR)" ]; then \
		rm -rf $(BUILD_DIR); \
	fi

fclean	:	clean
	if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi

re		:	fclean all

.PHONY	:	clean fclean re
.SILENT	:	clean fclean
