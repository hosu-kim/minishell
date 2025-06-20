/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_word_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:38:08 by jakand            #+#    #+#             */
/*   Updated: 2025/06/20 19:22:36 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	malloc_memory(t_cmd_token **new_token, int i)
{
	(*new_token)->cmd_with_args = malloc((i + 1) * sizeof(char *));
	if (!(*new_token)->cmd_with_args)
		return (1);
	(*new_token)->arg_types = malloc(i * sizeof(t_arg_type));
	if (!(*new_token)->arg_types)
		return (free((*new_token)->cmd_with_args), 1);
	return (0);
}

int	get_args_type(int type)
{
	if (type == T_WORD)
		return (UNQUOTED);
	if (type == T_Q_WORD)
		return (QUOTED);
	if (type == T_D_Q_WORD)
		return (DQUOTED);
	return (UNQUOTED);
}

int	is_text_token(t_token *lex_start, t_token **lex_token,
		t_cmd_token *new_token)
{
	int	i;
	
	i = 0;
	while (*lex_token && ((*lex_token)->type == T_WORD
		|| (*lex_token)->type == T_Q_WORD || (*lex_token)->type == T_D_Q_WORD))
	{
		i++;
		*lex_token = (*lex_token)->next;
	}
	if (malloc_memory(&new_token, i))
		return (1);
	*lex_token = lex_start;
	i = 0;
	while (*lex_token && ((*lex_token)->type == T_WORD
		|| (*lex_token)->type == T_Q_WORD || (*lex_token)->type == T_D_Q_WORD))
	{
		new_token->cmd_with_args[i] = ft_strdup((*lex_token)->value);
		new_token->arg_types[i] = get_args_type((*lex_token)->type);
		i++;
		*lex_token = (*lex_token)->next;
	}
	new_token->cmd_with_args[i] = NULL;
	new_token->argc = i;
	return (0);
}

int	is_pipe_token(t_token **lex_token, t_cmd_token *new_token)
{
	if (!(*lex_token) || (*lex_token)->type != T_PIPE)
		return (0);
	if ((*lex_token)->next == NULL || (*lex_token)->next->type == T_PIPE)
		return (printf("Syntax error\n"), 1);
	if ((*lex_token)->next->type != T_WORD
		&& (*lex_token)->next->type != T_Q_WORD
		&& (*lex_token)->next->type != T_D_Q_WORD)
		return (printf("Syntax error\n"), 1);
	(*lex_token) = (*lex_token)->next;
	new_token->has_pipe = 1;
	return (0);
}
