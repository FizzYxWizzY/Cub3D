# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 16:01:02 by mflury            #+#    #+#              #
#    Updated: 2022/11/30 17:00:09 by mflury           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
CC = @gcc
CFLAGS = -Wall -Werror -Wextra

SRC = $(SRC_P1) $(SRC_P2)

SRC_P1 = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_atoi.c \
	ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memcmp.c ft_memmove.c ft_memchr.c \
	ft_strlen.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_strnstr.c ft_toupper.c \
	ft_tolower.c ft_strlcat.c ft_strlcpy.c \
	ft_strdup.c ft_calloc.c \

SRC_P2 = \
	ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_striteri.c ft_strmapi.c \
	ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \

SRC_BONUS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	ft_lstadd_back_bonus.c ft_lstlast_bonus.c \
	ft_lstsize_bonus.c ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c ft_lstclear_bonus.c \
	ft_lstmap_bonus.c \

all : $(NAME)

$(NAME) : $(OBJ)
	@echo Creating static library
	@ar rcs $(NAME) $(OBJ)

bonus : $(OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

%.o : %.c
	@echo Creating objets files $<
	@$(CC) -o $@ -c $< $(CFLAGS)

clean :
	@echo Deleting objets files
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	@echo Deleting others files
	@rm -f $(NAME) $(NAME).tar.gz $(NAME).zip

re : fclean all

tar :
	@echo Creating TAR.GZ archive
	@tar -czvf $(NAME).tar.gz $(SRC) libft.h Makefile

zip :
	@echo Creating ZIP archive
	@zip -r $(NAME).zip $(SRC) libft.h Makefile

.PHONY : clean fclean re tar zip
