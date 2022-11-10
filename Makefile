# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 11:02:01 by vde-prad          #+#    #+#              #
#    Updated: 2022/11/10 17:19:55 by vde-prad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= pipex.c
OBJS	= ${SRCS:.c=.o}
NAME	= pipex
LIBRARY = libft/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

################# RULES #####################

all: lib comp
	
lib:
	@echo "\nCOMPILING LIBFT"
	@${MAKE} -C ./libft

comp: ${NAME}

$(NAME): ${OBJS}
	@echo "\nCOMPILING PIPEX"
	@${CC} ${CFLAGS} ${OBJS} ${LIBRARY} -o ${NAME}

clean:
	@echo "LIMPIANDO"
	@${MAKE} -C ./libft clean
	@${RM} ${OBJS}

fclean: clean
	@echo "LIMPIANDO"
	@${MAKE} -C ./libft fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
