/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/05 16:31:11 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

/**
 * @enum e_token_type
 * @brief Types of tokens produced by the lexer.
 */
typedef enum e_token_type
{
	TOK_WORD,      // a generic word or command name
	TOK_PIPE,      // |
	TOK_REDIR_IN,  // <
	TOK_REDIR_OUT, // >
	TOK_APPEND,    // >>
	TOK_HEREDOC,   // <<
	TOK_EOF,       // End-Of_File marker
} t_token_type;

/**
 * @struct s_token
 * @brief A node in a linked list of tokens
 */
typedef struct s_token
{
	t_token_type	type;   // token category
	char			*value; // literal text
	struct s_token	*next;  // next token in list
} t_token;

/* Primary lexer interface */
// Split the input line int a linked list of tokens.
t_token	*tokenize(const char *input);
// Free all tokens in the list.
void	free_tokens(t_token *head);

/* Reader helpers */
// Read a quoted substring and emit as a signle WORD token.
size_t	read_quoted(const char *in, size_t i, t_token **h, t_token *t);
// Read an unquoted word and emit as a WORD token.
size_t	read_word(const char *in, size_t i, t_token **h, t_token **t);
// Read a redirection operator (<, >, <<, >>) and emit corresponding token.
size_t	read_redir(const char *in, size_t i, t_token **h, t_token **t);

/* Utility helpers */
// Allocate a new token node with a copy of the text.
t_token	*new_token(t_token_type tyep, const char *s, size_t len);
// Append a token to the end of the linked list.
void	add_token(t_token **head, t_token **tail, t_token *tok);

#endif
