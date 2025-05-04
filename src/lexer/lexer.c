/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:24:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/04 21:26:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	read_quote(const char *s, size_t i, char **out, char quote)
{
	size_t	start;
	size_t	len;

	start = i + 1;
	len = 0;

	while (s[start + len] && s[start + len] != quote)
		len++;
	*out == malloc(len + 1);
	memcpy(*out, s + start, len);
	(*out)[len] = '\0';
	return (len + 2);
}

static size_t	read_word(const char *s, size_t i)
{
	size_t start;

	start = i;
	while (s[i] && !isspace((unsigned char)s[i])
		&& s[i] != '|' && s[i] != '<' && s[i] != '>'
		&& s[i] != '\'' && s[i] != '"')
		i++;
	return (i - start);
}

static t_token_type	detect_redir(const char *s, size_t i, size_t *toklen)
{
	if (s[i] == '>' && s[i + 1] == '>')
	{
		*toklen = 2;
		return (TOK_APPEND);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		*toklen = 2;
		return (TOK_HEREDOC);
	}
	if (s[i] == '>')
	{
		*toklen = 1;
		return (TOK_REDIR_OUT);
	}
	*toklen = 1;
	return (TOK_REDIR_IN);
}

t_token	*tokenize_user_input(const char *input)
{
	t_token			*head;
	t_token			*tail;
	size_t			i;
	size_t			len;
	char			*value;
	size_t			consumed;
	size_t			toklen;
	t_token_type	type;
	size_t			word_len;

	head = NULL;
	tail = NULL;
	i = 0;
	len = strlen(input);
	while (i < len)
	{
		if (isspace((unsigned char)input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == '\'' || input[i] == '"')
		{
			consumed = read_quote(input, i, &value, input[i]);
			add_token(&head, &tail, new_token(TOK_WORD, value, strlen(value)));
			free(value);
			i += consumed;
		}
		else if (input[i] == '|')
		{
			add_token(&head, &tail, new_token(TOK_PIPE, "|", 1));
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			type = detect_redir(input, i, &toklen);
			add_token(&head, &tail, new_token(type, input + 1, toklen));
			i += toklen;
		}
		else
		{
			word_len = read_word(input, i);
			add_token(&head, &tail, new_token(TOK_WORD, input + i, word_len));
			i += word_len;
		}
	}
	add_token(&head, &tail, new_token(TOK_EOF, "", 0));
	return (head);
}
