/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:50 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 15:26:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <minishell.h>

typedef struct s_cmd_token		t_cmd_token;
typedef struct s_redirection	t_redirection;

/* Executor functions */
int		executor(t_cmd_token *tokens, char ***envp);
int		execute_pipeline(t_cmd_token *cmds, char **envp);
void	execute_in_child(t_cmd_token *cmd, char **envp);
int		is_parent_builtin(const char *cmd);
void	setup_signal_handlers(void);

/* Execution utility functions */
int		check_empty_command(char **args);
void	run_external(char **argv, char **envp);
int		count_valid_args(t_cmd_token *cmd);
char	**create_filtered_args(t_cmd_token *cmd);
void	execute_with_path(char **argv, char **envp);

/* Redirection functions */
void	apply_redirections(t_cmd_token *cmd);
int		input_redirection(t_redirection *redir);
int		output_redirection(t_redirection *redir);
int		append_redirection(t_redirection *redir);
int		heredoc_redirection(t_redirection *redir);

/* Heredoc helper functions */
int		write_heredoc_lines(int out_fd, t_redirection *redir);
int		redirect_stdin_from_fd(int in_fd);

/* Pipeline utility functions */
void	setup_pipes(int *pipe_fd, int in_fd, int out_fd);
void	create_child_process(int in_fd, int out_fd, t_cmd_token *cmd, char **envp);
int		wait_for_pipeline_completion(pid_t last_pid);

#endif
