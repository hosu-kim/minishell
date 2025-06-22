/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:12:03 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 15:30:14 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	key_matches(char *env_var, char *key)
{
	int	i;

	i = 0;
	while (key[i] && env_var[i] && key[i] == env_var[i])
		i++;
	if (key[i] == '\0' && env_var[i] == '=')
		return (1);
	return (0);
}

static void	free_env_array(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static char	**remove_env_var(char **env, char *key)
{
	char	**new_env;
	int		count;
	int		i;
	int		j;

	if (!is_valid_identifier(key))
		return (env);
	count = count_env_vars(env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!key_matches(env[i], key))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				free_env_array(new_env);
				return (env);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_env_array(env);
	return (new_env);
}

int	builtin_unset(char **args, char ***env)
{
	int	i;
	int	exit_code;

	if (!args[1])
		return (0);
	exit_code = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(STDERR_FILENO, "minishell: unset: `", 19);
			write(STDERR_FILENO, args[i], ft_strlen(args[i]));
			write(STDERR_FILENO, "': not a valid identifier\n", 26);
			exit_code = 1;
		}
		else
			*env = remove_env_var(*env, args[i]);
		*env = remove_env_var(*env, args[i]);
		i++;
	}
	return (exit_code);
}
