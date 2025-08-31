NAME = mynginx

BUILD = docker build -t $(NAME) .

RUN = docker run --name $(NAME) -dp 8080:80 -v $$HOME/data:/mydata/ $(NAME)

STOP = docker stop $$(docker ps -qa)

RM = docker rm $$(docker ps -qa)

RMI  = docker rmi $$(docker images -q)

all	:	
	$(BUILD)
	$(RUN)

fclean:
	$(STOP)
	$(RM)
	$(RMI)


re: fclean all