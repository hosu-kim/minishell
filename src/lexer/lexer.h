/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/04 21:25:08 by hoskim           ###   ########seoul.kr  */
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
 * @brief A single node definition in a linked list of tokens
 * 
 * @param type The token's type (one of t_token type).
 * @param value The literal string value of the token.
 * @param next Pointer to the next token in the list.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;

t_token	*tokenize_user_input(const char *input);

t_token *new_token(t_token_type type, const char *start, size_t len);
void	add_token(t_token **head, t_token **tail, t_token *tok);
void	free_tokens(t_token *head);

#endif
