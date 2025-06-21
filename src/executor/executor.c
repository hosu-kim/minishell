/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:24 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 12:05:35 by hoskim           ###   ########seoul.kr  */
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

void	execute_in_child(t_cmd_token *cmd, char **envp)
{
	int	exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	apply_redirections(cmd);
	if (!cmd->cmd_with_args || !cmd->cmd_with_args[0])
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd->cmd_with_args[0]))
	{
		exit_code = execute_builtin(cmd, &envp);
		exit(exit_code);
	}
	run_external(cmd->cmd_with_args, envp);
}

int	executor(t_cmd_token *tokens, char ***envp)
{
	pid_t	pid;
	int		status;

	if (!tokens)
		return (0);
	if (tokens && !tokens->next_cmd_token
		&& is_parent_builtin(tokens->cmd_with_args[0]))
		return (execute_builtin(tokens, envp));
	if (tokens->next_cmd_token)
		return (execute_pipeline(tokens, *envp));
	setup_signal_handlers();
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		execute_in_child(tokens, *envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		tokens->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		tokens->exit_code = 128 + WTERMSIG(status);
	return (tokens->exit_code);
}
