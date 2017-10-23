# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpark <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/25 13:19:43 by cpark             #+#    #+#              #
#    Updated: 2017/03/26 16:12:11 by llefevre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rush-2

SRC = ft_fila.c \
	  ft_filb.c \
	  ft_filc.c \
	  ft_fild.c \
	  ft_file.c \
	  ft_list_c.c \
	  ft_list_l.c \
	  ft_print.c \
	  ft_search.c \
	  main.c

OBJ = ft_fila.o \
	  ft_filb.o \
	  ft_filc.o \
	  ft_fild.o \
	  ft_file.o \
	  ft_list_c.o \
	  ft_list_l.o \
	  ft_print.o \
	  ft_search.o \
	  main.o

all : $(NAME)

$(NAME) :
	@gcc -Wextra -Wall -Werror -o $(NAME) $(SRC)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all
