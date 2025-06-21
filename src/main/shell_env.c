/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:17:59 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 02:15:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_environment_variables(char **new_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_environment(char **env)
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
