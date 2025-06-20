/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:06:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/19 21:58:53 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*extract_key(char *arg, char *eq_pos)
{
	char	*key;
	int		key_len;
	int		i;

	key_len = eq_pos - arg;
	key = malloc(key_len + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	builtin_export(char **args, char ***env)
{
	char	*eq_pos;
	char	*key;
	char	*value;
	int		i;

	if (!args[1])
		return (builtin_env(*env));
	i = 1;
	while (args[i])
	{
		eq_pos = ft_strchr(args[i], '=');
		if (eq_pos)
		{
			key = extract_key(args[i], eq_pos);
			if (key)
			{
				value = ft_strdup(eq_pos + 1);
				*env = add_env_var(*env, key, value);
				free(key);
				free(value);
			}
		}
		i++;
	}
	return (0);
}
