/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:27:15 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 15:51:28 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_interrupt_signal(t_shell *shell)
{
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	shell->exit_status = 130;
}

static void	process_pending_signals(t_shell *shell)
{
	if (g_signal_received == SIGINT)
	{
		handle_interrupt_signal(shell);
		g_signal_received = 0;
	}
	else if (g_signal_received == SIGQUIT)
		g_signal_received = 0;
}

static char	*read_user_input(void)
{
	char	*line;

	line = readline("minishell> ");
	if (line && *line)
		add_history(line);
	return (line);
}

static int	is_valid_input(char *input)
{
	if (!input || !*input)
		return (0);
	return (1);
}

void	run_shell_loop(t_shell *shell)
{
	char	*input_line;

	while (1)
	{
		process_pending_signals(shell);
		input_line = read_user_input();
		if (!input_line)
			break ;
		if (is_valid_input(input_line))
			execute_input_line(shell, input_line);
		if (input_line)
			free(input_line);
	}
}
