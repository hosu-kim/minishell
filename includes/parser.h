/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:07:30 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 17:26:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "minishell.h"

typedef enum e_arg_type
{
	QUOTED,
	UNQUOTED,
	DQUOTED,
	SKIP_PRINT
}	t_arg_type;

typedef struct s_redirection
{
	t_token_type			type; // redirection type
	char					*target; // target file or heredoc delimiter
	t_arg_type				target_types;
	int						order; // original order in command
	struct s_redirection	*next; // pointer to next redirection
}	t_redirection;

typedef struct s_cmd_token
{
	char				**cmd_with_args; // args and command on 0 position
	int					argc; // amount of arguments
	//*arg_types: types of words (quotes - 0, double quotes - 2, no quotes - 1)
	t_arg_type			*arg_types;
	t_redirection		*input_redirs; // list of input redirections
	t_redirection		*output_redirs; // list of output redirections
	t_redirection		*all_redirs; // all redirections in original order
	int					has_pipe; // 1 pipe, 0 no pipe
	int					exit_code; // to store child’s exit status
	struct s_cmd_token	*next_cmd_token; // if pipe pointer to next command
}	t_cmd_token;

// prepare lexed tokens for execution
t_cmd_token		*parser(t_token *start);

// make word tokens for execution
int				is_text_token(t_token *lex_start, t_token **lex_token,
					t_cmd_token *new_token);

// make pipe tokens for execution
int				is_pipe_token(t_token **lex_token, t_cmd_token *new_token);

// make redir tokens for execution
int				is_redirection_token(t_token **lex_token,
					t_cmd_token *new_token);

// process single redirection at current position
int				process_redirection_at_position(t_token **lex_token,
					t_cmd_token *new_token);

// parser utility functions
int				count_args_in_command(t_token *token);
int				process_command_tokens(t_token **lexed_token,
					t_cmd_token *new_token, int argc);
t_token			*initialize_parser(t_token *start, t_cmd_token **cmd_start,
					t_cmd_token **current, t_cmd_token **new_token);

// free parsed tokens in parser
void			free_cmd_tokens(t_cmd_token *start);

// redirection utility functions
void			add_to_input_list(t_cmd_token *new_token,
					t_redirection *new_redir, t_redirection **current);
void			add_to_output_list(t_cmd_token *new_token,
					t_redirection *new_redir, t_redirection **current);
void			add_to_all_redirs(t_cmd_token *new_token,
					t_redirection *new_redir);
t_redirection	*create_redir_copy(t_redirection *original);
void			add_redir_to_all_list(t_cmd_token *token, t_redirection *copy);
int				get_args_type(int type);

#endif