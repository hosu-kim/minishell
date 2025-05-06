/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:37 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/05 20:20:54 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*tokenize(const char *input)
{
	t_token	*head = NULL;
	t_token	*tail = NULL;
	size_t	i;
	size_t	n;

	while (input[i])
	{
		if (input[i] == ' ')
		{
			++i;
			continue ;
		}
		if (input[i] == '\'' || input[i] == '"')
			n = read_quotes(input, i, &head, &tail);
		else if (input[i] == '|')
		{
			add_token(&head, &tail, new_token(TOK_PIPE, "|", 1));
			n = 1;
		}
		else if (input[i] == '<' || input[i] == '>')
			n = read_redir(input, i, &head, &tail);
		else
			n = read_word(input, i, &head, &tail);
		i += n;
	}
	add_token(&head, &tail, new_token(TOK_EOF, "", 0));
	return (head);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}
