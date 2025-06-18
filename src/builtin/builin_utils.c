/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:48:42 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 22:04:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd_token *cmd, char **envp)
{
	if (ft_strcmp(cmd->cmd_with_args[0], "echo") == 0)
		return (builtin_echo(cmd->cmd_with_args));
	if (ft_strcmp(cmd->cmd_with_args[0], "cd") == 0)
		return (builtin_cd(cmd->cmd_with_args), envp);
	if (ft_strcmp(cmd->cmd_with_args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->cmd_with_args[0], "export") == 0)
		return (build_export(cmd->cmd_with_args, &envp));
	if (ft_strcmp(cmd->cmd_with_args[0], "env") == 0)
		return (buildin_env(envp));
	if (ft_strcmp(cmd->cmd_with_args[0], "exit") == 0)
		return (builtin_exit(cmd->cmd_with_args));
	return (1);
}

char	*get_env_value(char *key, char **env)
{
	int		i;
	int		key_len;
	char	*eq_pos;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos && (eq_pos - env[i]) == key_len)
		{
			if (ft_strcmp(env[i], key, key_len) == 0)
				return (eq_pos + 1);
		}
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

char	**add_env_var(char **env, char *key, char *value)
{
	char	**new_env;
	char	*new_var;
	int		count;
	int		i;

	count = count_env_vars(env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_var = ft_strjoin(key, "=");
	if (value)
		new_var = ft_strjoin(new_var, value);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}
