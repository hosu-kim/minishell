/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:12:03 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/19 21:46:56 by hoskim           ###   ########seoul.kr  */
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

static char	**remove_env_var(char **env, char *key)
{
	char	**new_env;
	int		count;
	int		i;
	int		j;

	count = count_env_vars(env);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!key_matches(env[i], key))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	builtin_unset(char **args, char ***env)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		*env = remove_env_var(*env, args[i]);
		i++;
	}
	return (0);
}
