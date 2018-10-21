# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:21:18 by jplevy            #+#    #+#              #
#    Updated: 2018/10/21 18:57:27 by jplevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC = gcc
CFLAG = -Wall -Werror -Wextra
SRC_PATH = ./srcs/
SRC_NAME = ft_ssl.c
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./dst/
# SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INCLUDE_FILE = ./includes/ft_ssl.h
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating libft"
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null
	@$(CC) -o $(NAME) $(OBJ) -L. $(LIBFT_PATH)$(LIBFT_NAME)
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
