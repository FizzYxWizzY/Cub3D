# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 05:10:37 by mflury            #+#    #+#              #
#    Updated: 2024/03/21 22:49:11 by abourgue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	cub3D

OBJS	=	$(SOURCES:%.c=%.o)

SRC_DIR =	srcs/

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


SRCS	=	
			parsing.c \
			error.c \
			main.c \
			draw_map.c \
			draw_player.c \
			draw_utils.c \
			init_struct.c \
			move.c \
			raycasting.c \
			utils.c

SOURCES = $(addprefix $(SRC_DIR), $(SRCS))

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