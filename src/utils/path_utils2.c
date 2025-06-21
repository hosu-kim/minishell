/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:56:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 11:36:57 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_path_segment(char *path, int start, int end)
{
	char	*segment;
	int		len;
	int		i;

	len = end - start;
	segment = malloc(len + 1);
	if (!segment)
		return (NULL);
	i = 0;
	while (i < len && path[start + i])
	{
		segment[i] = path[start + i];
		i++;
	}
	segment[i] = '\0';
	return (segment);
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*result;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split_path(path_env);
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_paths(paths);
	return (result);
}

void	my_execvp(char *cmd, char **args, char **env)
{
	char	*path;

	if (!cmd || !args)
		return ;
	if (ft_strchr(cmd, '/'))
	{
		execve(cmd, args, env);
		return ;
	}
	path = find_executable(cmd);
	if (path)
	{
		execve(path, args, env);
		free(path);
	}
	else
		execve(cmd, args, env);
}