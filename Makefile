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

NAME_S = server

NAME_C = client

SRC_S = server.c

SRC_C = client.c

OBJ_S = server.o

OBJ_C = client.o

OBJ_BONUS_S = server_bonus.o

OBJ_BONUS_C = client_bonus.o

SERVER_BONUS = server_bonus.c

CLIENT_BONUS = client_bonus.c

HDR = minitalk.h

HDR_BONUS = minitalk_bonus.h

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJ_S)
	$(CC) $? -o $@

$(NAME_C): $(OBJ_C)
	$(CC) $? -o $@

%.o: %.c $(HDR)
	$(CC) $(FLAGS) -I.$(HDR) -c $< -o $@

bonus:
	@make OBJ_S="$(OBJ_BONUS_S)" OBJ_C="$(OBJ_BONUS_C)" HDR="$(HDR_BONUS)" all

clean:
	$(RM) *.o

fclean: clean
	$(RM) server client

re: fclean all

.PNONY:	all clean fclean re bonus