
SRCS =	main.c init_env.c clean_fd.c get_opt.c x.c main_loop.c \
	init_fd.c do_select.c check_fd.c \
	srv_create.c srv_accept.c \
	client_read.c client_write.c

OBJS = ${SRCS:.c=.o}

NAME = server

CFLAGS = -I. -g3 -Wall -Werror
LDFLAGS =

CC = gcc
RM = rm -f


client:
	gcc client.c -o client

server: ${OBJS}
	${CC} -o ${NAME} ${OBJS} ${LDFLAGS}


all: client server 

clean:
		${RM} ${OBJS} *~ #*#

fclean:		clean
		${RM} ${NAME}
		rm client

re:		fclean all
