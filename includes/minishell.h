/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:08 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 15:29:49 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Common includes */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Imports all environment variables on the current process. */
extern char **environ;

/* Module-specific headers */
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtin.h"
# include "signal_handler.h"
# include "utils.h"

/* Common macros */
# define SUCCESS 0
# define FAILURE 1
# define YES 1
# define NO 0
# define BUFFER_SIZE 1024

/* Main shell stucture */
typedef struct s_shell
{
	char	**env;         /* Environment variables */
	int		exit_status;   /* Last command exit status */
	char	*input;        /* Current input line */
	int		stdin_backup;  /* Backup of original stdin */
	int		stdout_backup; /* Backup of original stdout */
}	t_shell;

/* Global variable - ONLY ONE for signal handling */
extern int g_signal_received; /* Stores only the signal number */

/* Main functions */
int		initialize_shell(t_shell *shell);
void	run_shell_loop(t_shell *shell);
void	execute_input_line(t_shell *shell, char *input);
void	cleanup_shell(t_shell *shell);

/* Environment management functions */
int		copy_environment_variables(char **new_env, int count);
void	free_environment(char **env);

/* Error handling functions */
void	handle_tokenization_error(void);
void	handle_parsing_error(t_token *tokens);

/* Resource cleanup functions */
void	cleanup_parsing_resources(t_token *tokens, t_cmd_token *commands);

#endif
