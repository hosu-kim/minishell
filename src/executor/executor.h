/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:50 by jakand            #+#    #+#             */
/*   Updated: 2025/06/16 20:27:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../parser/parser.h"
#include "../expander/expander.h"
#include "../../include/minishell.h"

/* redirections.c */
int		input_redirection(t_redirection *redir);
int		output_redirection(t_redirection *redir);
int		append_redirection(t_redirection *redir);
int		heredoc_redirection(t_redirection *redir);
void	apply_redirections(t_cmd_token *cmd);

/* executor.c */
int		executor(t_cmd_token *tokens, char **envp);

/* pipeline.c */
int	execute_pipeline(t_cmd_token *cmds);

/* heredoc_helper.c */
int	write_heredoc_lines(int wfd, t_redirection *redir);
int	redirect_stdin_from_fd(int rfd);

#endif