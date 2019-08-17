# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/03/12 18:28:12 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re

NAME = ft_nm 

FLAGS = -Wall -Werror -Wextra
FLAGS += -g3
# FLAGS += -fsanitize=address,undefined
SRC_DIR = src

INCLUDE =  includes/\
		   -I ../includes/

SHARED_DIR = ../shared
OBJ_DIR = obj

SHARED_SRC = \
			 cpu_family.c\
			 cross_symbol.c\
			 mach_header.c\
			 ptr_utils.c

SRC =\
	 ft_alphacmp.c\
	 nlist.c\
	 nm.c\
	 nm_init.c\
	 segment_command.c\
	 symtab_command.c\
	 tree_tools.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

SHARED_SRCS = $(addprefix $(SHARED_DIR)/, $(SHARED_SRC))

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))
SHARED_OBJS = $(addprefix ../$(OBJ_DIR)/, $(addsuffix .o, $(basename $(SHARED_SRC))))

OBJ_FILES = $(sort $(dir $(OBJS) $(dir $SHARED_OBJS)))

LIBFT = ../libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

../$(OBJ_DIR)/%.o: $(SHARED_DIR)/%.c
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): obj_dir $(OBJS) $(SHARED_OBJS) 
	@make -C ../libft
	@gcc $(FLAGS) -o $(NAME) $(OBJS) $(SHARED_OBJS) -I $(INCLUDE) -L ../libft -l ft
	@echo $(NAME) is compiled

obj_dir:
	@mkdir -p $(OBJ_DIR) || true
	@mkdir -p ../$(OBJ_DIR) || true

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf ../$(OBJ_DIR)
	@make -C ../libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ../libft fclean

re: fclean all

