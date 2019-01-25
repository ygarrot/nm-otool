# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/01/25 18:41:27 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm 

FLAGS =-Wall -Werror -Wextra -g3

SRC_FOLDER = src/
INCLUDE =  includes/
OBJ_DIR = mkdir obj
SRC_FP = \

OBJ = $(addprefix $(SRC_FOLDER), $(SRC_FP:.c=.o))
LIBFT = libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@gcc $(FLAGS) -o $@ -c $< -I $(INCLUDE)

$(NAME): $(OBJ)
	@make -C nm 
	@make -C otool 

clean:
	@make -C nm
	@make -C otool 


fclean:
	make -C fclean nm
	make -C fclean otool

re: fclean all

.PHONY: $(NAME) all clean fclean re
