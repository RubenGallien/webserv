FILES = main.cpp \
	Server.cpp \
	Socket.cpp \
	Epoll.cpp \
	Utils/Signal.cpp

VERSION = -std=c++98

CLANG = c++

FLAGS = -Werror -Wall -Wextra

TARGET = webserv

DELETE = rm

all:
	$(CLANG) $(VERSION) $(FLAGS) -o $(TARGET) $(FILES)

fclean:
	$(DELETE) $(TARGET)
