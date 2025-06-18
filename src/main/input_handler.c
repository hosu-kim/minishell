/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:49:21 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 21:42:01 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_parsed_commands(t_shell *shell, t_token *tokens, t_cmd_token *commands)
{
	expand_token(commands);
	shell->exit_status = executor(commands, shell->env);
	cleanup_parsing_resources(tokens, commands);
}

static void	process_valid_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd_token *commands;

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
