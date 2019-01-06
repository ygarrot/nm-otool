# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/01/06 15:53:32 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_otool

FLAGS = -Wall -Werror -Wextra -g3
FLAGS +=  -fsanitize=address

SRC_FOLDER = src/
INCLUDE =  includes/\
					 -I ../includes/

OBJ_DIR = mkdir obj
# :r !ls
SRC_FP =\
					otool.c \
					section.c \
					otool_struct.c \
				  mach_header.c \
					cross_symbol.c\
					print_memory.c\
					cpu_family.c \
				ptr_utils.c\
					print_otool.c

ALL_SRC = $(SRC_FOLDER)/$(SRC_FP) + $(SHARED_FOLDER)/$(SHARED_SRC)
OBJ = $(addprefix $(SRC_FOLDER), $(SRC_FP:.c=.o))

LIBFT = ../libft/libft.a

all: $(NAME)

%.o: %.c
			@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): $(OBJ)
	@make -C ../libft -j
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(INCLUDE) -L ../libft -l ft

clean:
	@rm -f $(OBJ)
	@make -C ../libft clean

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f $(NAME_NO_HOST)
	@make -C ../libft fclean

re: fclean all

.PHONY: $(NAME) all clean fclean re
