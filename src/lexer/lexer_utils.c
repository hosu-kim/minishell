/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/17 12:57:25 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_token(t_token *token)
{
	t_token		*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->value)
			free(temp->value);
		if (temp)
			free(temp);
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
