/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/27 21:31:08 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_command	*cmd_list;
	char		*input;

	(void)argc;
	(void)argv;
	minishell_init(&shell, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		cmd_list = parse_input(input);
		free(input);
		if (cmd_list)
		{
			execute_command(&shell, cmd_list);
			free_command(cmd_list);
		}
	}
	minishell_cleanup(&shell);
	return (0);
}