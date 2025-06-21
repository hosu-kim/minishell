/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:06:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 02:01:42 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*extract_key(char *arg, char *address_of_equal_sign)
{
	char	*key;
	int		key_len;
	int		i;

	key_len = address_of_equal_sign - arg;
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

static void	process_export_arg(char *arg, char ***env)
{
	char	*address_of_equal_sign;
	char	*key;
	char	*value;

	address_of_equal_sign = ft_strchr(arg, '=');
	if (address_of_equal_sign)
	{
		key = extract_key(arg, address_of_equal_sign);
		if (key)
		{
			value = ft_strdup(address_of_equal_sign + 1);
			*env = add_env_var(*env, key, value);
			free(key);
			free(value);
		}
	}
}

int	builtin_export(char **args, char ***env)
{
	int	i;

	if (!args[1])
		return (builtin_env(*env));
	i = 1;
	while (args[i])
	{
		process_export_arg(args[i], env);
		i++;
	}
	return (SUCCESS);
}
