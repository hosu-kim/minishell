/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/17 15:11:25 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_token(t_token *token)
{
	t_token	*held_token;

	while (token)
	{
		held_token = token;
		token = token->next;
		if (held_token->value)
			free(held_token->value);
		if (held_token)
			free(held_token);
	}
}

int	skip_whitespaces(const char **input)
{
	while (**input == ' ' || (**input >= 9 && **input <= 13))
		(*input)++;
	if (**input == '\0')
		return (1);
	return (0);
}
