/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:50 by jakand            #+#    #+#             */
/*   Updated: 2025/06/13 20:37:30 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXERCUTOR_H
#define EXERCUTOR_H

#include "parser.h"

int	initialize_heredoc_temp_file(t_redirection *redir, int *expand_variables);
int	process_and_write_heredoc_input(int fd,
									t_redirection *redir, 
									int expand_variables);

#endif