/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:25:54 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/19 22:38:30 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**add_env_var(char **env, char *key, char *value)
{
	char	**new_env;
	char	*temp;
	char	*new_var;
	int		count;
	int		i;

	count = count_env_vars(env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < count)
		new_env[i] = ft_strdup(env[i]);
	temp = ft_strjoin(key, "=");
	if (value)
	{
		new_var = ft_strjoin(temp, value);
		free(temp);
	}
	else
		new_var = temp;
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}
