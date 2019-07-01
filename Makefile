# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yxie <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 09:26:38 by yxie              #+#    #+#              #
#    Updated: 2019/07/01 14:49:23 by yxie             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
LFT_FLAGS = -L $(LFT_PATH) -lft
INC_FLAGS = -I $(INC_PATH)

SRC_PATH = ./srcs/
INC_PATH = ./includes/
LFT_PATH = ./libft/

SRC_NAME = *.c

SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
all: $(NAME)

$(NAME):
	@make -C $(LFT_PATH)
	@gcc $(FLAGS) $(INC_FLAGS) $(SRCS) -o $(NAME) $(LFT_FLAGS)

clean:
	@make clean -C $(LFT_PATH)

fclean: clean
	@make fclean -C $(LFT_PATH)
	@rm -f fillit

re: fclean all
