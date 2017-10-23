# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpark <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/21 07:34:20 by cpark             #+#    #+#              #
#    Updated: 2017/03/22 13:10:01 by cpark            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCC = srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_strcmp.c srcs/ft_strlen.c srcs/ft_swap.c

SRCO = ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o

all : $(NAME)

$(NAME) : lib.o
	ar rc $(NAME) $(SRCO)

lib.o : 
	gcc -Wextra -Wall -Werror -c $(SRCC) -Iincludes

clean :
	/bin/rm -f *.o

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all
