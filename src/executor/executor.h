/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:50 by jakand            #+#    #+#             */
/*   Updated: 2025/06/15 22:40:33 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXERCUTOR_H
#define EXERCUTOR_H

#include "parser.h"
#include "expander.h"

int	write_heredoc_lines(int wfd, t_redirection *redir);
int	redirect_stdin_from_fd(int rfd);
int	execute_pipeline(t_cmd_token *cmds);

#endif