# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 14:47:37 by aerrazik          #+#    #+#              #
#    Updated: 2022/07/31 01:52:06 by aerrazik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
GCF = -Wall -Wextra -Werror
NAME = pipex
SRC = main.c ft_strjoin.c ft_split.c

OBJS = ${SRC: .c=.o}

%.o: %.c
			${CC} ${GCF} -c $<

all : $(NAME)

$(NAME) : $(OBJS)
			${CC} $(GCF) $(OBJS) -o $(NAME)

clean :
	rm -rf ${OBJS: .o}

fclean : clean
	rm -rf ${NAME}

re : fclean all