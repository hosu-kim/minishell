/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:11:38 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 13:25:52 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

/**
 * @brief Deallocates every value in a node and node itself.
 */
void	free_tokens(t_token *token)
{
	t_token	*held_token;

	while (token)
	{
		held_token = token;
		token = token->next;
		if (held_token->value)
			free(held_token->value);
		free(held_token);
	}
}

int	is_word_boundary(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r')
		|| c == '<' || c == '>' || c == '|' || c == '\0');
}

int	handle_single_quote(const char **input, int *pos, int *len)
{
	(*pos)++;
	while (*pos < (int)ft_strlen(*input) && (*input)[*pos] != '\''
		&& (*input)[*pos] != '\0')
	{
		(*len)++;
		(*pos)++;
	}
	if ((*input)[*pos] == '\'')
	{
		(*pos)++;
		return (1);
	}
	write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 41);
	return (0);
}

int	handle_double_quote(const char **input, int *pos, int *len)
{
	(*pos)++;
	while (*pos < (int)ft_strlen(*input) && (*input)[*pos] != '"'
		&& (*input)[*pos] != '\0')
	{
		(*len)++;
		(*pos)++;
	}
	if ((*input)[*pos] == '"')
	{
		(*pos)++;
		return (1);
	}
	write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 41);
	return (0);
}

int	process_quote_char(const char **input, int *pos, int *total_len, int *sq,
						int *dq)
{
	if ((*input)[*pos] == '\'')
	{
		*sq = 1;
		if (!handle_single_quote(input, pos, total_len))
			return (0);
	}
	else if ((*input)[*pos] == '"')
	{
		*dq = 1;
		if (!handle_double_quote(input, pos, total_len))
			return (0);
	}
	else
	{
		(*total_len)++;
		(*pos)++;
	}
	return (1);
}
