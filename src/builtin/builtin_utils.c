/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:48:42 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 22:11:22 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (NO);
	if (ft_strcmp(cmd, "echo") == 0)
		return (YES);
	if (ft_strcmp(cmd, "cd") == 0)
		return (YES);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (YES);
	if (ft_strcmp(cmd, "export") == 0)
		return (YES);
	if (ft_strcmp(cmd, "unset") == 0)
		return (YES);
	if (ft_strcmp(cmd, "env") == 0)
		return (YES);
	if (ft_strcmp(cmd, "exit") == 0)
		return (YES);
	return (NO);
}

int	execute_builtin(t_cmd_token *cmd, char ***envp)
{
	if (ft_strcmp(cmd->cmd_with_args[0], "echo") == 0)
		return (builtin_echo(cmd->cmd_with_args));
	if (ft_strcmp(cmd->cmd_with_args[0], "cd") == 0)
		return (builtin_cd(cmd->cmd_with_args, envp));
	if (ft_strcmp(cmd->cmd_with_args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->cmd_with_args[0], "export") == 0)
		return (builtin_export(cmd->cmd_with_args, envp));
	if (ft_strcmp(cmd->cmd_with_args[0], "unset") == 0)
		return (builtin_unset(cmd->cmd_with_args, envp));
	if (ft_strcmp(cmd->cmd_with_args[0], "env") == 0)
		return (builtin_env(*envp));
	if (ft_strcmp(cmd->cmd_with_args[0], "exit") == 0)
		return (builtin_exit(cmd->cmd_with_args));
	return (FAILURE);
}

static int	env_key_matches(char *env_var, char *key, int key_len)
{
	int	i;

	i = 0;
	while (i < key_len && env_var[i] && key[i] == env_var[i])
		i++;
	if (i == key_len && env_var[i] == '=')
		return (1);
	return (0);
}

char	*get_env_value(char *key, char **env)
{
	int	i;
	int	key_len;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (env_key_matches(env[i], key, key_len))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}
