# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 05:10:37 by mflury            #+#    #+#              #
#    Updated: 2024/10/21 08:46:38 by mflury           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	cub3D

OBJS	=	$(SRCS:%.c=%.o)

CC		=	gcc

RM      =	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	=	-Llibft -lft -Lgnl -l:get_next_line.a -L./minilibx/linux -lmlx -lXext -lX11 -lm -lbsd
	MLX_DIR = minilibx/linux
else
	LIBS = -Llibft -lft -Lgnl -l:get_next_line.a -L./minilibx/macOS -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = minilibx/macOS
endif

SRCS	=	doc/raycaster_flat2.c \
			srcs/error.c \
			srcs/parsing/parsing.c \
			srcs/parsing/parsing_textures.c \
			srcs/parsing/parsing_textures_utils.c \
			srcs/parsing/parsing_map.c \
			srcs/parsing/parsing_map_utils.c \
			srcs/render/create_trgb.c \
			# srcs/render/mlx_put_pixel_to_image.c \
			# srcs/moves/keeb_listener.c \
			# srcs/main.c \
			# srcs/render/render_window.c \

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