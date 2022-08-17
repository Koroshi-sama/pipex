# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 14:47:37 by aerrazik          #+#    #+#              #
#    Updated: 2022/08/17 09:24:51 by aerrazik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
GCF = -Wall -Wextra -Werror #-g -fsanitize=address
NAME = pipex
BO = pipex_bonus
SRC = main.c ft_strjoin.c ft_split.c get_next_line.c  err_sp_path.c\
		get_next_line_utils.c

BONUS =  main_bonus.c ft_strjoin.c ft_split.c get_next_line.c \
		get_next_line_utils.c cl_wt_sw_pipe_bonus.c here_doc_bonus.c \
		err_sp_path.c

OBJS = ${SRC:.c=.o}
BOBJS = ${BONUS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
			${CC} $(GCF) $(OBJS) -o $(NAME)

bonus : $(BO)

$(BO) : $(BOBJS)
			${CC} $(GCF) $(BOBJS) -o $(BO)

clean :
	rm -rf ${OBJS}
	rm -rf ${BOBJS}

fclean : clean
	rm -rf ${NAME}
	rm -rf ${BO}

re : fclean all
