/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:37 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 20:01:00 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	add_token_to_list(t_token *start, t_token *new_token)
{
	t_token	*current;

	current = start;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static t_token	*create_new_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = 0;
	new_token->value = NULL;
	new_token->next = NULL;
	return (new_token);
}

static int	process_tokenizing(const char **input_ptr, t_token *new_token)
{
	if (is_double_char_operator(input_ptr, new_token)
		|| is_single_char_operator(input_ptr, new_token)
		|| text_tokenizer(input_ptr, new_token))
		return (YES);
	return (NO);
}

static void	handle_successful_token(t_token **start, t_token *new_token)
{
	if (!*start)
		*start = new_token;
	else
		add_token_to_list(*start, new_token);
}

t_token	*tokenizer(const char *input)
{
	t_token		*start;
	t_token		*new_token;
	const char	**input_ptr;

	start = NULL;
	input_ptr = &input;
	while (**input_ptr != '\0')
	{
		if (skip_whitespaces(input_ptr) == FAILURE)
			break ;
		new_token = create_new_token();
		if (!new_token)
			return (free_tokens(start), NULL);
		if (process_tokenizing(input_ptr, new_token))
			handle_successful_token(&start, new_token);
		else
		{
			free(new_token);
			break ;
		}
	}
	return (start);
}
