# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 01:20:03 by mflury            #+#    #+#              #
#    Updated: 2023/02/12 01:20:03 by mflury           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NOT USABLE YET, NEED TO BE DONE #

NAME = get_next_line.a
OBJ = $(SRC:.c=.o)
CC = @gcc
CFLAGS = -Wall -Werror -Wextra

SRC = $(SRC_P1) $(SRC_P2)

SRC_P1 = \
	get_next_line.c \
	get_next_line_utils.c \
	\
	\
	\

SRC_P2 = \
	\
	\
	\

SRC_BONUS = \
	\
	\
	\


all : $(NAME)

$(NAME) : $(OBJ)
	@echo Creating static library
	@ar rcs $(NAME) $(OBJ)

%.o : %.c
	@echo Creating objets files $<
	@$(CC) -o $@ -c $< $(CFLAGS)

clean :
	@echo Deleting objets files
	@rm -f $(OBJ)

fclean : clean
	@echo Deleting others files
	@rm -f $(NAME) $(NAME).tar.gz $(NAME).zip

re : fclean all

tar :
	@echo Creating TAR.GZ archive
	@tar -czvf $(NAME).tar.gz $(SRC) get_next_line.h Makefile

zip :
	@echo Creating ZIP archive
	@zip -r $(NAME).zip $(SRC) get_next_line.h Makefile

.PHONY : clean fclean re tar zip
