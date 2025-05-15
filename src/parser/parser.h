/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:59:29 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/11 19:52:24 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../lexer/lexer.h"

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_cmd
{
	char			**argv;
	char			*heredoc_delimiter;
	char			*infile_name;
	char			*outfile_name;
	t_redir_type	input_redir_type;
	t_redir_type	output_redir_type;
	struct s_cmd	*next;
}	t_cmd;

#endif