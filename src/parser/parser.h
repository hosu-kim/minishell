/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:07:30 by jakand            #+#    #+#             */
/*   Updated: 2025/06/07 16:21:58 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../lexer/lexer.h"

typedef enum e_redir_type
{
	TOK_INPUT,  // <
	TOK_OUTPUT, // >
	TOK_APPEND, // >>
	TOK_HEREDOC // <<
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;         // redirection type
	char					*target;      // target file or heredoc delimiter
	int						target_types; // types of words (quotes - 0, double quotes - 2, no quotes - 1)
	struct s_redirection	*next;        // pointer to next redirection
}	t_redirection;

typedef struct s_command
{
	char				**args;        // args and command on 0 position
	int					argc;          // amount of arguments
	int					*args_types;   // types of words (quotes - 0, double quotes - 2, no quotes - 1)
	t_redirection		*input_redir;  // list of input redirections
	t_redirection		*output_redir; // list of output redirections
	int					pipe;          // 1 pipe, 0 no pipe
	struct s_command	*next;         // if pipe pointer to next command
}	t_command;

// prepare lexed tokens for execution
t_command	*parser(t_token *start);

// make word tokens for execution
int			pars_words(t_token *lex_start, t_token **lex_token,
		t_command *new_token);

// make pipe tokens for execution
int			pipe_tok(t_token **lex_token, t_command *new_token);

// make redir tokens for execution
int			redir_tok(t_token **lex_token, t_command *new_token);

// get type (word, quotes, double quotes)
int			get_args_type(int type);

// free parsed tokens in main
void		free_token_parsed(t_command *token_parsed);

// free parsed tokens in parser
void		free_command(t_command *start);


#endif