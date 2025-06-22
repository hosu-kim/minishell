/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:25:54 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 20:12:52 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*create_env_string(char *key, char *value)
{
	char	*temp;
	char	*new_var;

	temp = ft_strjoin(key, "=");
	if (value)
	{
		new_var = ft_strjoin(temp, value);
		free(temp);
	}
	else
		new_var = temp;
	return (new_var);
}

int	ft_compare(const void *s1, const void *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (void *)s1;
	str2 = (void *)s2;
	i = 0;
	while (str1[i] != '=')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	update_new_env(char *env, char *key, char *value, char **new_env)
{
	int	update;

	update = 0;
	if (!ft_compare(env, key))
	{
		*new_env = create_env_string(key, value);
		update = 1;
	}
	else
		*new_env = ft_strdup(env);
	return (update);
}

void	free_env(char **env, int i)
{
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**add_env_var(char **env, char *key, char *value)
{
	char	**new_env;
	int		update;
	int		count;
	int		i;

	count = count_env_vars(env);
	update = 0;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < count)
		update |= update_new_env(env[i], key, value, &new_env[i]);
	if (!update)
	{
		new_env[i] = create_env_string(key, value);
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free_env(env, i);
	return (new_env);
}
