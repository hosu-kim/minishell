/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 13:09:01 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/**
 * @brief Token types stored in the linked list.
 * @details
 * - enum: used to represent a fixed set of named constants.
 * - Heredoc(<<): Accepts multi-line input until it meets the delimiter
 *                provided on the right of the operator initially.
 */
typedef enum e_token_type
{
	T_WORD,
	T_Q_WORD,
	T_D_Q_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

/**
* @brief A node structure to store tokens in a linked list of tokens.
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* lexer.c */
// Split the input line into a linked list of tokens.
t_token	*tokenizer(const char *input);

/* lexer_utils.c */
// Free all tokens in the list.
void	free_tokens(t_token *token);
// Helper functions for text tokenizing
int		is_word_boundary(char c);
int		handle_single_quote(const char **input, int *pos, int *len);
int		handle_double_quote(const char **input, int *pos, int *len);
int		process_quote_char(
			const char **input, int *pos, int *total_len, int *sq, int *dq);

/* word_tokens.c */
// Make word tokens
int		text_tokenizer(const char **input, t_token *new_node);

int		is_single_char_operator(const char **input, t_token *new_token);
int		is_double_char_operator(const char **input, t_token *new_token);

#endif
