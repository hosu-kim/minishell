/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:08 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 17:53:16 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ========== INCLUDES ========== */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ========== MACROS ========== */
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1

/* Core utilities */
#include "utils.h"

/* Lexer and parser */
# include "lexer.h"
# include "parser.h"

/* Built-ins and execution */
# include "builtin.h"
# include "parser.h"
# include "executor.h"

# include "signal_handler.h"

#endif
