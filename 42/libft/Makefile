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

NAME1 = cust
NAME2 = comp

SRC = src/*.cpp rc.cpp

all : 1 2

1 : $(NAME1)

2 : $(NAME2)

re : fclean1 fclean2 $(NAME1) $(NAME2)

re1 : fclean1 $(NAME1)

re2 : fclean2 $(NAME2)

$(NAME1) :
	@g++ -o $(NAME1) -I src main.cpp $(SRC)
$(NAME2) :
	@g++ -o $(NAME2) -I src test.cpp $(SRC)
fclean : fclean1 fclean2

fclean1 :
	@rm $(NAME1)
fclean2 :
	@rm $(NAME2)
