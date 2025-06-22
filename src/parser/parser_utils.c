/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:00:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 16:56:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_args_in_command(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == T_WORD || token->type == T_Q_WORD
			|| token->type == T_D_Q_WORD)
			count++;
		else if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
			|| token->type == T_REDIR_APPEND || token->type == T_HEREDOC)
		{
			if (token->next)
				token = token->next;
		}
		token = token->next;
	}
	return (count);
}

static int	allocate_command_memory(t_cmd_token *new_token, int argc)
{
	new_token->cmd_with_args = malloc((argc + 1) * sizeof(char *));
	if (!new_token->cmd_with_args)
		return (1);
	new_token->arg_types = malloc(argc * sizeof(t_arg_type));
	if (!new_token->arg_types)
		return (free(new_token->cmd_with_args), 1);
	return (0);
}

static int	process_word_token(t_token **token, t_cmd_token *cmd, int *arg_idx)
{
	cmd->cmd_with_args[*arg_idx] = ft_strdup((*token)->value);
	cmd->arg_types[*arg_idx] = get_args_type((*token)->type);
	(*arg_idx)++;
	*token = (*token)->next;
	return (0);
}

static int	handle_token_processing(t_token **lexed_token,
		t_cmd_token *new_token, int *arg_index)
{
	if ((*lexed_token)->type == T_WORD || (*lexed_token)->type == T_Q_WORD
		|| (*lexed_token)->type == T_D_Q_WORD)
	{
		process_word_token(lexed_token, new_token, arg_index);
	}
	else if ((*lexed_token)->type == T_REDIR_IN
		|| (*lexed_token)->type == T_REDIR_OUT
		|| (*lexed_token)->type == T_REDIR_APPEND
		|| (*lexed_token)->type == T_HEREDOC)
	{
		if (process_redirection_at_position(lexed_token, new_token))
			return (1);
	}
	else
		*lexed_token = (*lexed_token)->next;
	return (0);
}

int	process_command_tokens(t_token **lexed_token, t_cmd_token *new_token,
		int argc)
{
	int	arg_index;

	if (allocate_command_memory(new_token, argc))
		return (1);
	arg_index = 0;
	while (*lexed_token && (*lexed_token)->type != T_PIPE)
	{
		if (handle_token_processing(lexed_token, new_token, &arg_index))
			return (1);
	}
	new_token->cmd_with_args[argc] = NULL;
	new_token->argc = argc;
	return (0);
}
