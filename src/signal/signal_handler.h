/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:34:59 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/16 19:53:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

#include "minishell.h"

extern volatile sig_atomic_t g_received_signal;

void	init_parent_signals(void);
void	init_child_signals(void);

#endif