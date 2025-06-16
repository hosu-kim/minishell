/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:30:05 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/16 19:55:22 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

volatile sig_atomic_t g_received_signal = 0;

static void	sigint_handler(int signo)
{
	g_received_signal = signo;
}

static void	sigquit_handler(int signo)
{
	g_received_signal = signo;
}

void	init_parent_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
