# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 20:19:48 by hoskim            #+#    #+#              #
#    Updated: 2025/06/22 22:01:44 by jaandras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iincludes

SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, \
    builtin/builtin_utils.c \
    builtin/cd.c \
    builtin/echo.c \
    builtin/env.c \
    builtin/env_utils.c \
    builtin/exit.c \
    builtin/export.c \
    builtin/export_utils.c \
    builtin/pwd.c \
    builtin/unset.c \
    executor/execution_utils.c \
    executor/executor.c \
    executor/file_checker.c \
    executor/heredoc_helpers.c \
    executor/pipeline.c \
    executor/pipeline_utils.c \
    executor/redirections.c \
    executor/signal_handler.c \
    expander/expander.c \
    expander/expander_utils.c \
    expander/update_token.c \
    lexer/lexer.c \
    lexer/lexer_operators.c \
    lexer/lexer_utils.c \
    lexer/text_tokenizer.c \
    main/input_error.c \
    main/input_handler.c \
    main/main.c \
    main/shell_cleanup.c \
    main/shell_env.c \
    main/shell_init.c \
    main/shell_loop.c \
    parser/free_command.c \
    parser/parser.c \
    parser/parse_redir_tokens.c \
    parser/parser_init.c \
    parser/parser_redirections.c \
    parser/parser_redir_utils.c \
    parser/parser_utils.c \
    parser/pipe_word_token.c \
	utils/ft_itoa.c \
    utils/path_utils2.c \
    utils/path_utils3.c \
    utils/path_utils.c \
    utils/str_utils.c \
    utils/utils.c \
    )
# SRCS = $(wildcard $(SRCS_DIR)/**/*.c) $(wildcard $(SRCS_DIR)/*.c)
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
