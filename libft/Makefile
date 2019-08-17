# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/08/17 12:38:21 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re libftasm libft

NAME = libft.a

LIBFTC_DIR = libft
LIBFTASM_DIR = libftasm

LIBC = $(LIBFTC_DIR)/libft.a
LIBASM = $(LIBFTASM_DIR)/libfts.a

all: $(NAME)

libftasm:
	@make -C $(LIBFTASM_DIR)

libftc:
	@make -C $(LIBFTC_DIR)

$(NAME): libftc libftasm
	libtool -static -o $(NAME) $(LIBC) $(LIBASM)
	ranlib $(NAME)

clean:
	@make clean -C $(LIBFTC_DIR)
	@make clean -C $(LIBFTASM_DIR)

fclean:
	@make fclean -C $(LIBFTC_DIR)
	@make fclean -C $(LIBFTASM_DIR)
	rm $(NAME)

re: fclean all
