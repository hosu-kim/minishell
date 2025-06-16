# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 20:19:48 by hoskim            #+#    #+#              #
#    Updated: 2025/06/16 20:14:38 by hoskim           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
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
		$(UTILS_DIR)/readline_wrapper.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iinclude -Isrc/builtin -Isrc/executor -Isrc/lexer -Isrc/expander -Isrc/parser -Isrc/utils

SRCS_DIR = src
SRCS = $(wildcard $(SRCS_DIR)/**/*.c) $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re