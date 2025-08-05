FILES = main.cpp \
	Server/Server.cpp \
	Server/Socket.cpp \
	Server/Epoll.cpp \
	Server/ClientManager.cpp \
	Server/HTTPRequest.cpp \
	Server/Client.cpp \
	Server/Utils/Signal.cpp

VERSION = -std=c++98

INCLUDES = -I includes -I includes/Server -I includes/Server/Utils

CLANG = c++

FLAGS = -Werror -Wall -Wextra -g

TARGET = webserv

DELETE = rm

all:
	$(CLANG) $(INCLUDES) $(VERSION) $(FLAGS) -o $(TARGET) $(FILES)

fclean:
	$(DELETE) $(TARGET)
