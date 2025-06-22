/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:30:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 17:29:09 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <errno.h>

static int	execute_cmd_with_path(char *cmd, char **args, char **env)
{
	char	*path;

	path = find_executable(cmd);
	if (path)
	{
		execve(path, args, env);
		perror(path);
		free(path);
		if (errno == EACCES)
			return (126);
		return (EXIT_FAILURE);
	}
	perror(cmd);
	return (127);
}

int	my_execvp(char *cmd, char **args, char **env)
{
	if (!cmd || !args || cmd[0] == '\0')
		return (127);
	if (ft_strchr(cmd, '/'))
	{
		execve(cmd, args, env);
		perror(cmd);
		if (errno == EACCES)
			return (126);
		if (errno == ENOENT)
			return (127);
		return (EXIT_FAILURE);
	}
	return (execute_cmd_with_path(cmd, args, env));
}
