# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/26 18:36:04 by mmeredit          #+#    #+#              #
#    Updated: 2021/12/26 18:42:13 by mmeredit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk.a

SERVER = server.c

CLIENT = client.c

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: server client

server: server.o
	$(CC) -o $@ $<

client: client.o
	$(CC) -o $@ $<

%.o:%.c 
	$(CC) -c $(FLAGS) -c $?

clean:
	$(RM) server.o client.o

fclean: clean
	$(RM) server client

re: clean fclean all

.PNONY:	all clean fclean re