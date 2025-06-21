/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:06:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 19:13:13 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (NO);
	if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
		&& *str != '_')
		return (NO);
	i = 1;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i]<= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')) && str[i] != '_')
			return (NO);
		i++;
	}
	return (YES);
}

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

static int	handle_export_error(char *arg)
{
	write(STDERR_FILENO, "minishell: export: `", 20);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	return (YES);
}

static int	process_export_arg(char *arg, char ***env)
{
	char	*address_of_equal_sign;
	char	*key;
	char	*value;

	address_of_equal_sign = ft_strchr(arg, '=');
	if (address_of_equal_sign)
	{
		key = extract_key(arg, address_of_equal_sign);
		if (!key || !is_valid_identifier(key))
		{
			if (key)
				free(key);
			return (handle_export_error(arg));
		}
		value = ft_strdup(address_of_equal_sign + 1);
		*env = add_env_var(*env, key, value);
		free(key);
		free(value);
	}
	else
	{
		if (!is_valid_identifier(arg))
			return (handle_export_error(arg));
		*env = add_env_var(*env, arg, "");
	}
	return (SUCCESS);
}

int	builtin_export(char **args, char ***env)
{
	int	i;
	int	exit_code;

	if (!args[1])
		return (builtin_env(*env));
	exit_code = 0;
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env) == 1)
		exit_code = 1;
		i++;
	}
	return (exit_code);
}
