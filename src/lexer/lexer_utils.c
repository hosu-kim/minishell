/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/17 20:43:37 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Deallocates every value in a node and node itself
 * 		  in *token linked list.
 */
void	free_token(t_token *token)
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
	while (**input == ' ' || (**input >= 9 && **input <= 13))
		(*input)++;
	if (**input == '\0')
		return (1);
	return (0);
}
