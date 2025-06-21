/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 12:52:05 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*initialize_t_command_pointers(
				t_token *lex_start, t_cmd_token **start,
				t_cmd_token **current, t_cmd_token **new_token)
{
	(*start) = NULL;
	(*current) = NULL;
	(*new_token) = NULL;
	return (lex_start);
}

static void	*initialize_new_token_members(t_cmd_token *new_token)
{
	new_token->cmd_with_args = NULL;
	new_token->argc = 0;
	new_token->arg_types = NULL;
	new_token->input_redirs = NULL;
	new_token->output_redirs = NULL;
	new_token->has_pipe = 0;
	new_token->next_cmd_token = NULL;
	return (new_token);
}

static void	make_token_list(t_cmd_token **start, t_cmd_token *new_token,
		t_cmd_token **current)
{
	if (!(*start))
		(*start) = new_token;
	else
		(*current)->next_cmd_token = new_token;
	(*current) = new_token;
}

static int	process_token_types(
			t_token **lexed_token, t_cmd_token *new_parsed_token)
{
	if (is_text_token(*lexed_token, lexed_token, new_parsed_token)
		|| is_redirection_token(lexed_token, new_parsed_token)
		|| is_pipe_token(lexed_token, new_parsed_token))
		return (1);
	return (0);
}

t_cmd_token	*parser(t_token *lex_start)
{
	t_token		*lexed_token;
	t_cmd_token	*start;
	t_cmd_token	*current;
	t_cmd_token	*new_parsed_token;

	lexed_token = initialize_t_command_pointers(lex_start, &start,
			&current, &new_parsed_token);
	while (lexed_token)
	{
		new_parsed_token = malloc(sizeof(t_cmd_token));
		if (!new_parsed_token)
			return (free_cmd_tokens(start), NULL);
		initialize_new_token_members(new_parsed_token);
		if (process_token_types(&lexed_token, new_parsed_token))
		{
			free(new_parsed_token);
			if (start)
				free_cmd_tokens(start);
			return (NULL);
		}
		make_token_list(&start, new_parsed_token, &current);
	}
	return (start);
}
