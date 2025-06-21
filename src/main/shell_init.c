/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:31:03 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 12:31:07 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_environment_variables(void)
{
	int	count;

	count = 0;
	while (environ[count])
		count++;
	return (count);
}

static char	**allocate_environment_array(int count)
{
	char	**env_array;

	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	env_array[count] = NULL;
	return (env_array);
}

static char	**create_environment_copy(void)
{
	int		env_count;
	char	**new_env;

	env_count = count_environment_variables();
	new_env = allocate_environment_array(env_count);
	if (!new_env)
		return (NULL);
	if (!copy_environment_variables(new_env, env_count))
	{
		free_environment(new_env);
		return (NULL);
	}
	return (new_env);
}

static void	init_shell_members(t_shell *shell)
{
	shell->env = NULL;
	shell->exit_status = 0;
	shell->input = NULL;
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
}

int	initialize_shell(t_shell *shell)
{
	init_shell_members(shell);
	shell->env = create_environment_copy();
	if (!shell->env)
		return (0);
	return (1);
}
