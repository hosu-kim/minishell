/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:07:30 by jakand            #+#    #+#             */
/*   Updated: 2025/06/16 18:58:13 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

typedef enum e_arg_type
{
	QUOTED,
	UNQUOTED,
	DQUOTED,
	SKIP_PRINT
}	t_arg_type;

typedef enum e_redir_type
{
	REDIR_INPUT,  // <
	REDIR_OUTPUT, // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}	t_redir_type;

typedef struct s_redirection
{
    t_redir_type			type;         // redirection type
    char					*target;      // target file or heredoc delimiter
    t_arg_type				target_types;
    struct s_redirection	*next;        // pointer to next redirection
}   t_redirection;

typedef struct s_cmd_token
{
	char				**cmd_with_args; // args and command on 0 position
	int					argc;			 // amount of arguments
	t_arg_type			*arg_types;		 // types of words (quotes - 0, double quotes - 2, no quotes - 1)
	t_redirection		*input_redirs;	 // list of input redirections
	t_redirection		*output_redirs;	 // list of output redirections
	int					has_pipe;        // 1 pipe, 0 no pipe
	int					exit_code;		 // to store child’s exit status
	struct s_cmd_token	*next_cmd_token; // if pipe pointer to next command
}	t_cmd_token;

// prepare lexed tokens for execution
t_cmd_token	*parser(t_token *start);

// make word tokens for execution
int			is_text_token(t_token *lex_start, t_token **lex_token,
		t_cmd_token *new_token);

// make pipe tokens for execution
int			is_pipe_token(t_token **lex_token, t_cmd_token *new_token);

// make redir tokens for execution
int			is_redirection_token(t_token **lex_token, t_cmd_token *new_token);

// get type (word, quotes, double quotes)
int			get_args_type(int type);

// free parsed tokens in main
void		free_token_parsed(t_cmd_token *token_parsed);

// free parsed tokens in parser
void		free_command(t_cmd_token *start);


#endif