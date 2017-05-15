#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: cpark <tytytr2@gmail.com>                  +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/05/12 15:30:01 by cpark             #+#    #+#             *#
#*   Updated: 2017/05/12 15:30:08 by cpark            ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = test

SRC = src/ft_putstr.cpp src/ft_putnbr.cpp rc.cpp

all : $(NAME)

re : fclean $(NAME)

$(NAME) :
	@g++ -o $(NAME) -I src main.cpp $(SRC)
fclean :
	@rm $(NAME)
