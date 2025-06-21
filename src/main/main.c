/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:14:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 16:31:19 by jaandras         ###   ########.fr       */
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
