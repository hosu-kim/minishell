# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 20:19:48 by hoskim            #+#    #+#              #
#    Updated: 2025/04/29 20:13:41 by hoskim           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
CFLAGS = -WALL -Wextra -Werror

SRCS_DIR = ./src
BUILTIN_DIR = $(SRCS_DIR)/builtin
EXECUTOR_DIR = $(SRCS_DIR)/executor
PARSER_DIR = $(SRCS_DIR)/parser
UTILS_DIR = $(SRCS_DIR)/utils

SRCS = $(SRCS_DIR)/minishell.c \
		$(BUILTIN_DIR)/builtin.c \
		$(EXECUTOR_DIR)/executor.c \
		$(PARSER_DIR)/parser.c \
		$(UTILS_DIR)/utils.c \
		4(UTILS_DIR)/readline_wrapper.c

OBJS = $(SRCS:.c=.o)
INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re