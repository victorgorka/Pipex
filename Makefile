# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 11:02:01 by vde-prad          #+#    #+#              #
#    Updated: 2022/11/08 14:59:00 by vde-prad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= pipex.c
OBJS	= ${SRCS:.c=.o}
NAME	= pipex.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: ${NAME}

%.o:.c

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
