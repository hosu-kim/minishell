/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:07:30 by jakand            #+#    #+#             */
/*   Updated: 2025/05/18 14:01:17 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../lexer/lexer.h"

typedef enum e_redir_type
{
    TOK_INPUT,		// <
	TOK_OUTPUT,	    // >
	TOK_APPEND,	    // >>
    TOK_HEREDOC		// <<
}   t_redir_type;

typedef struct s_redirection
{
    t_redir_type            type;       // redirection type
    char                    *target;    // target file or heredoc delimiter
    struct s_redirection    *next;      // pointer to next redirection
}   t_redirection;

typedef struct s_command
{
    char                **args;             // args and command on 0 pozition
    int                 arc;                // amount of arguments
    t_redirection       *input_redir;       // list of input redirections
    t_redirection       *output_redir;      // list of output redirections
    struct s_command    *next;              // if pipe pointer to next command
}   t_command;

t_command	*parser(t_token *start);

#endif