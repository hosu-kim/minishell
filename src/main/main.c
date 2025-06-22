/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:14:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 17:25:12 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Only ONE global variable for signal - stores signal number only */
int	g_signal_received = 0;

int	main(void)
{
	t_shell	shell;
	int		exit_code;

	if (!initialize_shell(&shell))
	{
		printf("minishell: initialization failed");
		return (EXIT_FAILURE);
	}
	setup_signal_handlers();
	run_shell_loop(&shell);
	exit_code = shell.exit_status;
	cleanup_shell(&shell);
	return (exit_code);
}
