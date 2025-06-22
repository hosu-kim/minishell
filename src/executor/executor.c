/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:24 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 17:18:32 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_builtin_execution(t_cmd_token *cmd, char **filtered_args,
		char **envp)
{
	char	**original_args;
	int		exit_code;

	original_args = cmd->cmd_with_args;
	cmd->cmd_with_args = filtered_args;
	exit_code = execute_builtin(cmd, &envp);
	cmd->cmd_with_args = original_args;
	free(filtered_args);
	exit(exit_code);
}

void	execute_in_child(t_cmd_token *cmd, char **envp)
{
	char	**filtered_args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	apply_redirections(cmd);
	if (!cmd->cmd_with_args || !cmd->cmd_with_args[0])
		exit(EXIT_SUCCESS);
	filtered_args = create_filtered_args(cmd);
	if (!filtered_args)
		exit(EXIT_SUCCESS);
	if (check_empty_command(filtered_args) != 0)
	{
		free(filtered_args);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(filtered_args[0]))
		handle_builtin_execution(cmd, filtered_args, envp);
	run_external(filtered_args, envp);
	free(filtered_args);
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
