/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:39:04 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 13:42:59 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	update_pwd_env(char ***env, char *old_pwd, char *new_pwd)
{
	char	**temp_env;

	temp_env = add_env_var(*env, "OLDPWD", old_pwd);
	if (!temp_env)
		return (1);
	free_environment(*env);
	*env = temp_env;
	temp_env = add_env_var(*env, "PWD", new_pwd);
	if (!temp_env)
		return (FAILURE);
	free_environment(*env);
	*env = temp_env;
	return (SUCCESS);
}

static char	*get_cd_path(char **args)
{
	char	*path;

	if (args[1] && args[2])
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (NULL);
	}
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		return (path);
	}
	return (args[1]);
}

int	builtin_cd(char **args, char ***env)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (FAILURE);
	path = get_cd_path(args);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (FAILURE);
	return (update_pwd_env(env, old_pwd, new_pwd));
}
