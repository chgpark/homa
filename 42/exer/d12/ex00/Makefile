# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpark <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/24 13:52:38 by cpark             #+#    #+#              #
#    Updated: 2017/03/24 14:32:40 by cpark            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file

SRC = main.c ft_err.c

all : $(NAME)

$(NAME) :
	gcc -o $(NAME) $(SRC)

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
