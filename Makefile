# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:21:18 by jplevy            #+#    #+#              #
#    Updated: 2018/11/21 13:22:09 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC = gcc
CFLAG = -Wall -Werror -Wextra
SRC_PATH = ./srcs/
SRC_NAME = ft_ssl.c \
			printing.c \
			ft_md5_hashs.c \
			ft_sha256_hashs.c \
			init.c \
			parsing_launching.c \
			ft_md5_core.c
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./dst/
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INCLUDE_FILE = ./includes/ft_ssl.h
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating libft"
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null
	@$(CC) -o $(NAME) $(OBJ) -L. $(LIBFT_PATH)$(LIBFT_NAME) -lm
	@echo "  Well done"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c  $(INCLUDE_FILE)
	@echo $@
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAG) -o $@ -c $<  -I./includes
	@echo "  Well done"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all

TOTO = toto
