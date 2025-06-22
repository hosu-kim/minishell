/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:49:21 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 18:38:25 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_file_descriptors(t_shell *shell)
{
	if (shell->stdin_backup != -1)
	{
		dup2(shell->stdin_backup, STDIN_FILENO);
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
	if (shell->stdout_backup != -1)
	{
		dup2(shell->stdout_backup, STDOUT_FILENO);
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
}

static void	execute_parsed_commands(t_shell *shell, t_token *tokens,
									t_cmd_token *commands)
{
	int	result;

	expand_token(commands, shell->exit_status);
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	result = executor(commands, &shell->env);
	if (result >= EXIT_SHELL)
	{
		shell->should_exit = 1;
		shell->exit_status = result - EXIT_SHELL;
	}
	else
		shell->exit_status = result;
	restore_file_descriptors(shell);
	cleanup_parsing_resources(tokens, commands);
}

static void	process_valid_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd_token	*commands;

	commands = parser(tokens);
	if (!commands)
	{
		handle_parsing_error(tokens);
		return ;
	}
	execute_parsed_commands(shell, tokens, commands);
}

void	execute_input_line(t_shell *shell, char *input)
{
	t_token	*tokens;

	shell->input = input;
	tokens = tokenizer(input);
	if (!tokens)
	{
		handle_tokenization_error();
		return ;
	}
	process_valid_tokens(shell, tokens);
}
