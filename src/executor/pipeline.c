/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:05:12 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 22:14:56 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_parent_builtin(const char *cmd)
{
	if (!cmd)
		return (NO);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (YES);
	return (NO);
}

static pid_t	execute_single_pipe(t_cmd_token *cmd, int in_fd, int *pipe_fd,
								char **envp)
{
	pid_t	pid;
	int		out_fd;
	int		in_out[2];

	in_out[0] = in_fd;
	if (cmd->next_cmd_token)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), -1);
		in_out[1] = pipe_fd[1];
	}
	else
		out_fd = STDOUT_FILENO;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
		create_child_process(in_out, pipe_fd, cmd, envp);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (pid);
}

static pid_t	handle_pipe_setup(t_cmd_token *current, int in_fd,
					int *pipe_fd, char **envp)
{
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pid = execute_single_pipe(current, in_fd, pipe_fd, envp);
	if (pipe_fd[0] != -1)
	{
		if (in_fd != STDIN_FILENO)
			close(in_fd);
	}
	return (pid);
}

int	execute_pipeline(t_cmd_token *cmds, char **envp)
{
	t_cmd_token	*current;
	int			in_fd;
	int			pipe_fd[2];
	pid_t		last_pid;
	pid_t		pid;

	current = cmds;
	in_fd = STDIN_FILENO;
	last_pid = -1;
	while (current)
	{
		pid = handle_pipe_setup(current, in_fd, pipe_fd, envp);
		if (!current->next_cmd_token)
			last_pid = pid;
		if (pipe_fd[0] != -1)
			in_fd = pipe_fd[0];
		current = current->next_cmd_token;
	}
	return (wait_for_pipeline_completion(last_pid));
}
