FILES = main.cpp \
	Server/Server.cpp \
	Server/Socket.cpp \
	Server/Epoll.cpp \
	Utils/Signal.cpp

VERSION = -std=c++98

CLANG = c++

FLAGS = -Werror -Wall -Wextra -g

TARGET = webserv

DELETE = rm

all:
	$(CLANG) $(VERSION) $(FLAGS) -o $(TARGET) $(FILES)

fclean:
	$(DELETE) $(TARGET)
