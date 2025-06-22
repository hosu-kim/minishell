/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:40:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 22:15:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	setup_pipes(int *pipe_fd, int in_fd, int out_fd)
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

void	create_child_process(int *in_out, int *pipe_fd, t_cmd_token *cmd,
		char **envp)
{
	setup_pipes(pipe_fd, in_out[0], in_out[1]);
	execute_in_child(cmd, envp);
}

int	wait_for_pipeline_completion(pid_t last_pid)
{
	int		status;
	pid_t	finished_pid;

	finished_pid = wait(&status);
	while (finished_pid > 0)
	{
		if (finished_pid == last_pid)
		{
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				return (128 + WTERMSIG(status));
		}
		finished_pid = wait(&status);
	}
	return (0);
}
