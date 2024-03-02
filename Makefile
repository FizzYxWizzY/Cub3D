# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 05:10:37 by mflury            #+#    #+#              #
#    Updated: 2024/03/02 23:12:41 by mflury           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	cub3D

OBJS	=	$(SRCS:%.c=%.o)

CC		=	gcc

RM      =	rm -f

CFLAGS	=	-Wall -Wextra -Werror

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	=	-Llibft -lft -L./minilibx/linux -lmlx -lXext -lX11 -lm -lbsd
	MLX_DIR = minilibx/linux
else
	LIBS = -Llibft -lft -L./minilibx/macOS -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = minilibx/macOS
endif

SRCS	=	error.c \
			parsing.c \
			main.c \

all: $(NAME)

%.o:%.c
			@echo Creating objets files $<
			${CC} ${CFLAGS} -Ilibft -Ignl -I${MLX_DIR} -c $? -o $@

${NAME}:	${OBJS}
			@make -C libft
			@make -C gnl
			@make -C ${MLX_DIR}
			${CC} ${CFLAGS} $^ ${LIBS} -o ${NAME}

clean:
			@echo Deleting objets files
			${RM} $(OBJS)
			@make -C libft clean
			@make -C gnl clean
			@make -C ${MLX_DIR} clean

fclean:		clean
			@echo Deleting others files
			${RM} $(NAME)
			@make -C libft fclean
			@make -C gnl fclean

re:	fclean all

.PHONY:	all clean fclean re