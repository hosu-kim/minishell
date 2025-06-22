/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:00:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 15:26:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include <errno.h>

int	check_empty_command(char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (127);
	return (0);
}

int	count_valid_args(t_cmd_token *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!cmd->cmd_with_args || !cmd->arg_types)
		return (0);
	while (cmd->cmd_with_args[i])
	{
		if (cmd->arg_types[i] != SKIP_PRINT)
			count++;
		i++;
	}
	return (count);
}

char	**create_filtered_args(t_cmd_token *cmd)
{
	char	**filtered_args;
	int		count;
	int		i;
	int		j;

	count = count_valid_args(cmd);
	if (count == 0)
		return (NULL);
	filtered_args = malloc(sizeof(char *) * (count + 1));
	if (!filtered_args)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd->cmd_with_args[i])
	{
		if (cmd->arg_types[i] != SKIP_PRINT)
			filtered_args[j++] = cmd->cmd_with_args[i];
		i++;
	}
	filtered_args[j] = NULL;
	return (filtered_args);
}

void	run_external(char **argv, char **envp)
{
	int	exit_code;

	if (ft_strchr(argv[0], '/'))
		execute_with_path(argv, envp);
	else
	{
		exit_code = my_execvp(argv[0], argv, envp);
		exit(exit_code);
	}
}
