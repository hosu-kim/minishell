/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:05:12 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 02:16:44 by hoskim           ###   ########seoul.kr  */
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

static void	setup_pipes(int *pipe_fd, int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

static void	create_child_process(int in_fd, int out_fd, t_cmd_token *cmd, char **envp)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	setup_pipes(pipe_fd, in_fd, out_fd);
	execute_in_child(cmd, envp);
}

static int	execute_single_pipe(t_cmd_token *cmd, int in_fd, int *pipe_fd, char **envp)
{
	pid_t	pid;
	int		out_fd;

	if (cmd->next_cmd_token)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), -1);
		out_fd = pipe_fd[1];
	}
	else
		out_fd = STDOUT_FILENO;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
		create_child_process(in_fd, out_fd, cmd, envp);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (pipe_fd[0]);
}

int	execute_pipeline(t_cmd_token *cmds, char **envp)
{
	t_cmd_token	*current;
	int			in_fd;
	int			pipe_fd[2];
	int			status;

	current = cmds;
	in_fd = STDIN_FILENO;
	while (current)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		in_fd = execute_single_pipe(current, in_fd, pipe_fd, envp);
		current = current->next_cmd_token;
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
