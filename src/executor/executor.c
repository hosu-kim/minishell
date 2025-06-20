/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:24 by jakand            #+#    #+#             */
/*   Updated: 2025/06/20 19:37:38 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	run_external(char **argv, char **envp)
{
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, envp);
	else
		my_execvp(argv[0], argv, envp);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

static int	exec_single(t_cmd_token *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	apply_redirections(cmd);
	if (is_builtin(cmd->cmd_with_args[0]))
		return (execute_builtin(cmd, envp));
	run_external(cmd->cmd_with_args, envp);
	return (EXIT_FAILURE);
}

void	execute_command(t_cmd_token *cmd, char **envp)
{
	if (!cmd || !cmd->cmd_with_args || !cmd->cmd_with_args[0])
		exit(1);
	apply_redirections(cmd);
	if (is_builtin(cmd->cmd_with_args[0]))
	{
		execute_builtin(cmd, envp);
		exit(0);
	}
	else
		run_external(cmd->cmd_with_args, envp);
}

int	executor(t_cmd_token *tokens, char **envp)
{
	pid_t	pid;
	int		status;

	if (!tokens)
		return (0);
	if (tokens && !tokens->next_cmd_token && is_builtin(tokens->cmd_with_args[0]))
		return (execute_builtin(tokens, envp));
	if (tokens->next_cmd_token)
		return (execute_pipeline(tokens, envp));
	setup_signal_handlers();
	pid = fork();
	if (pid == 0)
		exit(exec_single(tokens, envp));
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			tokens->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			tokens->exit_code = 128 + WTERMSIG(status);
		return (tokens->exit_code);
	}
	return (1);
}
