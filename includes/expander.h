/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:55 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 02:08:06 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "parser.h"

// Make expander for $
void	expand_token(t_cmd_token *token, int exit_status);

// Updating token
void	update_token(char **arg, char *start, int j);

// Remaking token
void	remake_token(char **arg, char *start, char *var, int j);

// Helper functions
int		is_valid_var_char(char c);
void	process_token_args(t_cmd_token *token, int exit_status);
char	*get_variable_value(char *env, int exit_status);
int		make_env(t_cmd_token **token, int i, int j, int exit_status);
char	*extract_var_name(char *arg, int start, int end);
char	*start_of_env(char *arg);

#endif
