/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/16 20:39:44 by jakand           ###   ########.fr       */
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
# include "../utils/utils.h"

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
// Skip whitespaces
int		skip_whitespaces(const char **input);
// Free all tokens in the list.
void	ft_free_token(t_token *token);
// Make word tokens
int	char_tokens(const char ***input, t_token *new_token);

#endif
