# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 20:35:44 by egeorgel          #+#    #+#              #
#    Updated: 2023/02/10 02:06:14 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c parsing.c utils.c

BNS_SRC = main.c parsing_b.c utils.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BNS_SRC:.c=.o)
NAME = pipex

ifdef WITH_BONUS
OBJS = $(BOBJ)
else
OBJS = $(OBJ)
endif

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB) Makefile
	cd libft ; make
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

bonus:
	@${MAKE} WITH_BONUS=1

clean:
	rm -f $(OBJ) $(BOBJ)
	cd libft ; make clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

PHONY: all bonus clean fclean re
