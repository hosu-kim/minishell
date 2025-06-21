/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:50 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 13:06:30 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include <sys/wait.h>

/* Executor functions */
int		executor(t_cmd_token *tokens, char ***envp);
int		execute_pipeline(t_cmd_token *cmds, char **envp);
void	execute_in_child(t_cmd_token *cmd, char **envp);
int		is_parent_builtin(const char *cmd);
void	setup_signal_handlers(void);

/* Redirection functions */
void	apply_redirections(t_cmd_token *cmd);
int		input_redirection(t_redirection *redir);
int		output_redirection(t_redirection *redir);
int		append_redirection(t_redirection *redir);
int		heredoc_redirection(t_redirection *redir);

/* Heredoc helper functions */
int		write_heredoc_lines(int out_fd, t_redirection *redir);
int		redirect_stdin_from_fd(int in_fd);

#endif
