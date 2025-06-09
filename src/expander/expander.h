/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:55 by jakand            #+#    #+#             */
/*   Updated: 2025/06/09 15:01:14 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "../parser/parser.h"

// Make expander for $
void	expand_token(t_cmd_token *token);

// Updating token
void	update_token(char **arg, char *start, int j);

// Remaking token
void	remake_token(char **arg, char *start, char *var, int j);

#endif
