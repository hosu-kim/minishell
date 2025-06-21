/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:51:09 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 15:59:11 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_parsing_resources(t_token *tokens, t_cmd_token *commands)
{
	if (tokens)
	{
		free_tokens(tokens);
	}
	if (commands)
	{
		free_cmd_tokens(commands);
	}
}

static void	restore_file_descriptor(int *backup_fd, int standard_fd)
{
	if (*backup_fd != -1)
	{
		dup2(*backup_fd, standard_fd);
		close(*backup_fd);
		*backup_fd = -1;
	}
}

static void	restore_standard_file_descriptors(t_shell *shell)
{
	restore_file_descriptor(&shell->stdin_backup, STDIN_FILENO);
	restore_file_descriptor(&shell->stdout_backup, STDOUT_FILENO);
}

void	free_shell_resources(t_shell *shell)
{
	if (shell->env)
		free_environment(shell->env);
	shell->input = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	free_shell_resources(shell);
	restore_standard_file_descriptors(shell);
}
