#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>


#define PORT 8888
#define MAX_EVENTS 10