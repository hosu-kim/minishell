/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:25:54 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 02:01:42 by hoskim           ###   ########seoul.kr  */
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

char	**add_env_var(char **env, char *key, char *value)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < count)
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = create_env_string(key, value);
	new_env[i + 1] = NULL;
	return (new_env);
}
