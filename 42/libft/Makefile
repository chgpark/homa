# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpark <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 15:38:10 by cpark             #+#    #+#              #
#    Updated: 2017/03/29 15:39:36 by cpark            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC=gcc
CFLAGS=-I
OBJ=libft.o

NAME=testlibft

SRC=src/*.c

all: $(NAME)

re: fclean all

$(NAME):
	@$(CC) -Wall -Wextra -Werror -o  $(NAME) $(SRC) $(NAME).c

fclean: clean
	@rm -f $(NAME)
clean:
	@rm -f *.o
