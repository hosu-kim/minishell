/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:12:48 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 20:26:46 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_single_char_operator(const char **input, t_token *new_token)
{
	if (**input == '|')
	{
		new_token->type = T_PIPE;
		new_token->value = ft_strdup("|");
		(*input)++;
		return (YES);
	}
	else if (**input == '<' && (*input)[1] != '<')
	{
		new_token->type = T_REDIR_IN;
		new_token->value = ft_strdup("<");
		(*input)++;
		return (YES);
	}
	else if (**input == '>' && (*input)[1] != '>')
	{
		new_token->type = T_REDIR_OUT;
		new_token->value = ft_strdup(">");
		(*input)++;
		return (YES);
	}
	return (NO);
}

int	is_double_char_operator(const char **input, t_token *new_token)
{
	if (**input == '<' && (*input)[1] == '<')
	{
		new_token->type = T_HEREDOC;
		new_token->value = ft_strdup("<<");
		(*input) += 2;
		return (YES);
	}
	else if (**input == '>' && (*input)[1] == '>')
	{
		new_token->type = T_REDIR_APPEND;
		new_token->value = ft_strdup(">>");
		(*input) += 2;
		return (YES);
	}
	return (NO);
}
