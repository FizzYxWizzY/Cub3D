# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 05:10:37 by mflury            #+#    #+#              #
#    Updated: 2024/02/17 05:24:53 by mflury           ###   ########.fr        #
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

SRCS	=	\

all: $(NAME)

%.o:%.c
			${CC} ${CFLAGS} -Iincludes -Ilibft -I${MLX_DIR} -c $? -o $@

${NAME}:	${OBJS}
			@make -C libft
			@make -C ${MLX_DIR}
			${CC} ${CFLAGS} $^ ${LIBS} -o ${NAME}

clean:
			${RM} $(OBJS)
			@make -C libft clean
			@make -C ${MLX_DIR} clean

fclean:		clean
			${RM} $(NAME)
			@make -C libft fclean

re:	fclean all

.PHONY:	all clean fclean re