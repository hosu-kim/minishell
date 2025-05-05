/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/05 16:46:29 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Creates a new node having a token info
t_token *new_token(t_token_type type, const char *start, size_t len)
{
	t_token *tok;

	tok = malloc(sizeof(*tok));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = malloc(len + 1);
	if (!tok->value)
	{
		free(tok);
		return (NULL);
	}
	memcpy(tok->value, start, len);
	tok->value[len] = '\0';
	tok->next = NULL;
	return (tok);
}

/**
 * @breif Append a token node to the linked list.
 */
void	add_token(t_token **head, t_token **tail, t_token *tok)
{
	if(!*head)
		*head = tok;
	else
		(*tail)->next = tok;
	*tail = tok;
}

