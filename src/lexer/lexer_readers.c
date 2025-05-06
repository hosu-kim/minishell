/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_readers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:31:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/05 20:22:39 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Read a quoted substring and add it as a TOK_WORD.
 * 
 * @param input Full input string.
 * @param i     Current index at opening quote.
 * @param h     Head of token list.
 * @param t     Tail of token list.
 * @return Number of characters consumed (including both quotes).
 */
size_t	read_quotes(const char *input, size_t i, t_token **h, t_token **t)
{
	char	quote = input[i];
	size_t	start;
	size_t	len;

	start = i + 1;
	len = 0;
	while (input[start + len] && input[start + len] != quote)
		++len;
	add_token(h, t, new_token(TOK_WORD, input + start, len));
	return (len + 2)
}

/**
 * Read a contiguous unquoted word.
 * @return Number of characters consumed.
 */
size_t	read_word(const char *input, size_t i, t_token **h, t_token **t)
{
	size_t	start;

	start = i;
	while (input[i] && !isspace((unsigned char)input[i])
			&& input[i] != '|'
			&& input[i] != '<'
			&& input[i] != '>'
			&& input[i] != '\''
			&& input[i] != '"')
	{
		++i;
	}
	add_token(h, t, new_token(TOK_WORD, in + start, i - start));
	return (i - start);
}

/**
 * Read a redirection operator and emit its token.
 * Supports: > < >> <<.
 */
size_t	read_redir(const char **input, size_t i, t_token **h, t_token **t)
{
	t_token_type	type;
	size_t			len;

	if (input[i] == '>' && input[i + 1] == '>')
	{
		type = TOK_APPEND;
		len = 2;
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		type = TOK_HEREDOC;
		len = 2;
	}
	else if (input[i] == '>')
	{
		type = TOK_REDIR_OUT;
		len = 1;
	}
	else
	{
		type = TOK_REDIR_IN;
		len = 1;
	}
	add_token(h, t, new_token(type, in + i, len));
	return (len);
}
