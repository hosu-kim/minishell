/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:00:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 15:26:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid_identifier(const char *str)
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

char	*extract_key(char *arg, char *address_of_equal_sign)
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

int	handle_export_error(char *arg)
{
	write(STDERR_FILENO, "minishell: export: `", 20);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	return (YES);
}

int	handle_export_with_value(char *arg, char *equal_sign, char ***env)
{
	char	*key;
	char	*value;

	key = extract_key(arg, equal_sign);
	if (!key || !is_valid_identifier(key))
	{
		if (key)
			free(key);
		return (handle_export_error(arg));
	}
	value = ft_strdup(equal_sign + 1);
	*env = add_env_var(*env, key, value);
	free(key);
	free(value);
	return (SUCCESS);
}

int	handle_export_without_value(char *arg, char ***env)
{
	if (!is_valid_identifier(arg))
		return (handle_export_error(arg));
	*env = add_env_var(*env, arg, "");
	return (SUCCESS);
}
