/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:05:12 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 19:57:08 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	create_child_process(int in_fd, int out_fd, t_cmd_token *cmd)
{
	pid_t	pid = fork();

	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
			dup2(in_fd, STDIN_FILENO);
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO);
		apply_redirections(cmd);
		execute_command(cmd);
		exit(0);
	}
	else if (pid < 0)
		perror("fork");
}

static int	setup_pipe_and_fork(int prev_fd, int pipefd[2], t_cmd_token *cmd)
{
	if (pipe(pipefd) < 0)
		perror("pipe");
	create_child_process(prev_fd, pipefd[1], cmd);
	close(pipefd[1]);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	return (pipefd[0]);
}

static void	fork_last(int prev_fd, t_cmd_token *cmd)
{
	create_child_process(prev_fd, STDOUT_FILENO, cmd);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
}

static void	wait_all(void)
{
	while (wait(NULL) > 0)
		;
}

int	execute_pipeline(t_cmd_token *cmds)
{
	int			prev_fd = STDIN_FILENO;
	int			pipefd[2];
	t_cmd_token	*cur = cmds;

	while (cur->has_pipe)
	{
		prev_fd = setup_pipe_and_fork(prev_fd, pipefd, cur);
		cur = cur->next_cmd_token;
	}
	fork_last(prev_fd, cur);
	wait_all();
	return (0);
}
