/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/15 18:43:11 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/**
 * @brief Definition of token types stored by the lexer
 * @details
 * Heredoc(<<): Accepts multi-line input until it meets the delimiter
 * 				provided on the right of the operator initionally.
 */
typedef enum e_token_type
{
	T_WORD,			// words or arguments
	T_D_Q_WORD,		// words in double quotes
	T_PIPE,			// |
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_REDIR_APPEND,	// >>
	T_HEREDOC		// <<
}	t_token_type;

/**
* @struct s_token
* @brief A node in a linked list of tokens
*/

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/* Primary lexer interface */
// Split the input line int a linked list of tokens.
t_token	*tokenize(const char *input);
// Free all tokens in the list.
void	free_tokens(t_token *head);

/* Reader helpers */
// Read a quoted substring and emit as a signle WORD token.
size_t	read_quotes(const char *input, size_t i, t_token **h, t_token **t);
// Read an unquoted word and emit as a WORD token.
size_t	read_word(const char *in, size_t i, t_token **h, t_token **t);
// Read a redirection operator (<, >, <<, >>) and emit corresponding token.
size_t	read_redir(const char *in, size_t i, t_token **h, t_token **t);

/* Utility helpers */
// Allocate a new token node with a copy of the text.
t_token	*new_token(t_token_type tyep, const char *s, size_t len);
// Append a token to the end of the linked list.
void	add_token(t_token **head, t_token **tail, t_token *tok);

// Free allocated token memory
void	ft_free_token(t_token *token);

#endif
