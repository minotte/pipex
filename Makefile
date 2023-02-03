# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nminotte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/22 16:47:18 by nminotte          #+#    #+#              #
#    Updated: 2023/01/30 14:22:51 by nminotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pi

SRC = ./pipex.c.c \
	  ./parsing.c \
	  \
	
OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/libft.a

CC = clang

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)


	
clean :
	@make clean -C ./libft
	@rm -rf $(OBJS)
	
fclean : clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean re fclean
