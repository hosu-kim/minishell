/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:08 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/27 22:27:03 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Nccesary standard library includes
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

// sub-module header includes
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include "utils.h"

// Global structure: Saves the state of the minishell
typedef struct s_shell
{
	char	**envp;	// Copy of the environment variables
	int		last_exit_status; // The most recent status of end of a command
}	t_shell;

// Main function definition
void	minishell_init(t_shell *shell, char **envp);
void	minishell_cleanup(t_shell *shell);
void	print_prompt(void);

#endif
