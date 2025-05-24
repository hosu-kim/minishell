/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:11:38 by jakand            #+#    #+#             */
/*   Updated: 2025/05/24 22:31:17 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Deallocates every value in a node and node itself.
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
	while (**input == ' ' || (**input >= '\t' && **input <= '\r'))
		(*input)++;
	if (**input == '\0')
		return (0);
	return (1);
}
