# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feedme <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/02 18:11:53 by feedme            #+#    #+#              #
#    Updated: 2018/09/12 10:14:25 by feedme           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = libft/*.c srcs/*.c 

BINARIES = *.o

FLAGS = -Wall -Wextra -Werror

all :$(NAME)

$(NAME): libftprintf.h
	gcc $(FLAGS) -c $(SRC) -I libftprintf.h
	ar rc $(NAME) $(BINARIES)
	ranlib $(NAME)

clean:
	rm -f $(BINARIES)
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
