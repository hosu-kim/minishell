/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 12:59:23 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*environment_variable(char *arg, int j)
{
	int	end;

	end = find_var_end(arg, j);
	return (extract_var_name(arg, j, end));
}

static int	handle_null_variable(t_cmd_token **token, int i, int j, char **env,
								char **start)
{
	if ((*token)->arg_types[i] < SKIP_PRINT)
	{
		update_token(&(*token)->cmd_with_args[i], *start, j);
		if ((*token)->cmd_with_args[i][0] == '\0')
			(*token)->arg_types[i] = SKIP_PRINT;
		free_var(env, start);
		return (1);
	}
	free_var(env, start);
	return (0);
}

int	make_env(t_cmd_token **token, int i, int j, int exit_status)
{
	char	*env;
	char	*var;
	char	*start;

	start = start_of_env((*token)->cmd_with_args[i]);
	env = environment_variable((*token)->cmd_with_args[i], j);
	var = get_variable_value(env, exit_status);
	if (var == NULL)
		return (handle_null_variable(token, i, j, &env, &start));
	remake_token(&(*token)->cmd_with_args[i], start, var, j);
	if (ft_strcmp(env, "?") == 0 || ft_strcmp(env, "$") == 0)
		free(var);
	free_var(&env, &start);
	return (1);
}

void	expand_token(t_cmd_token *token, int exit_status)
{
	while (token)
	{
		process_token_args(token, exit_status);
		token = token->next_cmd_token;
	}
}

char	*get_variable_value(char *env, int exit_status)
{
	char	exit_status_str[12];

	if (ft_strcmp(env, "?") == 0)
	{
		snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);
		return (ft_strdup(exit_status_str));
	}
	else if (ft_strcmp(env, "$") == 0)
	{
		snprintf(exit_status_str, sizeof(exit_status_str), "%d", getpid());
		return (ft_strdup(exit_status_str));
	}
	return (getenv(env));
}
