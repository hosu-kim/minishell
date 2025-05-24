/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:37 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/24 22:30:46 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	single_char_tokens(const char ***input, t_token *new_token)
{
	if (***input == '|')
	{
		new_token->type = T_PIPE;
		new_token->value = ft_strdup("|");
		(**input)++;
		return (1);
	}
	else if (***input == '<' && (**input)[1] != '<')
	{
		new_token->type = T_REDIR_IN;
		new_token->value = ft_strdup("<");
		(**input)++;
		return (1);
	}
	else if (***input == '>' && (**input)[1] != '>')
	{
		new_token->type = T_REDIR_OUT;
		new_token->value = ft_strdup(">");
		(**input)++;
		return (1);
	}
	return (0);
}

int	double_char_tokens(const char ***input, t_token *new_token)
{
	if (***input == '<' && (**input)[1] == '<')
	{
		new_token->type = T_HEREDOC;
		new_token->value = ft_strdup("<<");
		(**input) += 2;
		new_token->next = NULL;
		return (1);
	}
	else if (***input == '>' && (**input)[1] == '>')
	{
		new_token->type = T_REDIR_APPEND;
		new_token->value = ft_strdup(">>");
		(**input) += 2;
		new_token->next = NULL;
		return (1);
	}
	return (0);
}

int	add_new_token(const char **input, t_token *new_token,
					t_token **start, t_token **current)
{
	if (!single_char_tokens(&input, new_token))
	{
		if (!double_char_tokens(&input, new_token))
			if (insert_textual_token(&input, new_token))
				return (1);
	}
	if (!(*start))
	{
		*start = new_token;
		*current = *start;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
	return (0);
}

t_token	*tokenize(const char *input)
{
	t_token		*start;
	t_token		*new_token;
	t_token		*current;

	start = NULL;
	new_token = NULL;
	current = NULL;
	while (*input != '\0')
	{
		if (!skip_whitespaces(&input))
			break ;
		new_token = malloc(sizeof(t_token));
		if (new_token)
		{
			new_token->type = 0;
			new_token->value = NULL;
			new_token->next = NULL;
		}
		if (add_new_token(&input, new_token, &start, &current))
			return (free_token(new_token), free_token(start), NULL);
	}
	return (start);
}
