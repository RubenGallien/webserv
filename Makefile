FILES = main.cpp

VERSION = -std=c++98

CLANG = c++

FLAGS = -Werror -Wall -Wextra

TARGET = webserv

DELETE = rm

all:
	$(CLANG) $(VERSION) $(FLAGS) -o $(TARGET) $(FILES)

clean:
	$(DELETE) $(TARGET)
