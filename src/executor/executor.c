/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:24 by jakand            #+#    #+#             */
/*   Updated: 2025/06/16 18:58:44 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	g_received_signal = 0;

static void	handle_signal(int sig)
{
	g_received_signal = sig;
}

static void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	run_external(char **argv, char **envp)
{
	execve(argv[0], argv, envp);
	execvp(argv[0], argv);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

static int	exec_single(t_cmd_token *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->cmd_with_args[0]))
		return (execute_builtin(cmd, envp));
	run_external(cmd->cmd_with_args, envp);
	return (EXIT_FAILURE);
}

int	executor(t_cmd_token *tokens, char **envp)
{
	pid_t	pid;
	int		status;

	setup_signal_handlers();
	while (tokens)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
			exit(exec_single(tokens, envp));
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				tokens->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				tokens->exit_code = 128 + WTERMSIG(status);
		}
		tokens = tokens->next_cmd_token;
	}
	return (0);
}
