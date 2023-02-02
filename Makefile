# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 01:27:28 by ma1iik            #+#    #+#              #
#    Updated: 2023/02/01 16:49:15 by ma1iik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d
HEADERS			=	cub3d.h
CC				= 	gcc
RM				= 	rm -rf
CFLAGS 			=  -Wall -Wextra -Werror -Wno-unused-variable -g -fsanitize=address

SRCS	=	srcs/main.c \
			srcs/utils.c \
			srcs/drawing.c \
			srcs/move1.c \
			srcs/parsing1.c \
			srcs/parsing2.c

OBJS	= ${SRCS:.c=.o}

UNAME_S				= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS 			= -L ./libft -lft -lmlx -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	LIBS 			= -L ./libft -lft -lmlx -framework OpenGL -framework AppKit -lz
endif

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME} -lm

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re