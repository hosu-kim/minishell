/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:11:38 by jakand            #+#    #+#             */
/*   Updated: 2025/06/17 21:36:59 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

/**
 * @brief Skips leading whitespaces by advancing the input pointer.
 */
int	skip_whitespaces(const char **input)
{
	while (**input == ' ' || (**input >= '\t' && **input <= '\r'))
		(*input)++;
	if (**input == '\0')
		return (0);
	return (1);
}
