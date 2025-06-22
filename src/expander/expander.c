/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 21:59:32 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*environment_variable(char *arg, int j)
{
	int	end;

	end = find_var_end(arg, j);
	return (extract_var_name(arg, j, end));
}

static int	handle_null_variable(t_cmd_token **token, int i, int j, char **vars)
{
	if ((*token)->arg_types[i] < SKIP_PRINT)
	{
		update_token(&(*token)->cmd_with_args[i], vars[1], j);
		if ((*token)->cmd_with_args[i][0] == '\0')
			(*token)->arg_types[i] = SKIP_PRINT;
		free_var(&vars[0], &vars[1]);
		return (1);
	}
	free_var(&vars[0], &vars[1]);
	return (0);
}

int	make_env(t_cmd_token **token, int i, int j, int exit_status)
{
	char	*env;
	char	*var;
	char	*start;
	char	*vars[2];

	start = start_of_env((*token)->cmd_with_args[i]);
	env = environment_variable((*token)->cmd_with_args[i], j);
	var = get_variable_value(env, exit_status);
	if (var == NULL)
	{
		vars[0] = env;
		vars[1] = start;
		return (handle_null_variable(token, i, j, vars));
	}
	remake_token(&(*token)->cmd_with_args[i], start, var, j);
	if ((*token)->cmd_with_args[i][0] == '\0')
		(*token)->arg_types[i] = SKIP_PRINT;
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
	char	*value;
	char	*exit_code;
	char	*result;

	exit_code = ft_itoa(exit_status);
	if (ft_strcmp(env, "?") == 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		result = ft_strdup(exit_code);
		free(exit_code);
		return (result);
	}
	else if (ft_strcmp(env, "$") == 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		result = ft_strdup(exit_code);
		free(exit_code);
		return (result);
	}
	free(exit_code);
	value = getenv(env);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
