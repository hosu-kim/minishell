/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:55 by jakand            #+#    #+#             */
/*   Updated: 2025/06/08 00:23:44 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "../parser/parser.h"

// Make expander for $
void	expand_token(t_command *token);

// Updating token
void	update_token(char **arg, char *start, int j);

// Remaking token
void	remake_token(char **arg, char *start, char *var, int j);

#endif
