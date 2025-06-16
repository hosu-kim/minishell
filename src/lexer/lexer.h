/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/16 20:18:56 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../include/minishell.h"

/**
 * @brief Token types stored in the linked list.
 * @details
 * - enum: used to represent a fixed set of named constants.
 * - Heredoc(<<): Accepts multi-line input until it meets the delimiter
 * 				  provided on the right of the operator initionally.
 */
typedef enum e_token_type
{
	T_WORD,			// words or arguments
	T_Q_WORD,		// words in sigle quotes
	T_D_Q_WORD,		// words in double quotes
	T_PIPE,			// |
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_REDIR_APPEND,	// >>
	T_HEREDOC		// <<
}	t_token_type;

/**
* @brief A node structure to store tokens in a linked list of tokens.`
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* lexer.c */
// Split the input line int a linked list of tokens.
t_token	*tokenizer(const char *input);

/* lexer_utils.h */
// Skip whitespaces
int		skip_whitespaces(const char **input);
// Free all tokens in the list.
void	free_token(t_token *token);

/* word_tokens.c */
// Make word tokens
int	text_tokenizer(const char ***input, t_token *new_node);

#endif
