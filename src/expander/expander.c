/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 12:03:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	find_var_end(char *arg, int start)
{
	int	i;

	i = start + 1;
	if (arg[i] == '?' || arg[i] == '$')
		i++;
	else
	{
		while (is_valid_var_char(arg[i]))
			i++;
	}
	return (i);
}

static char	*environment_variable(char *arg, int j)
{
	int	end;

	end = find_var_end(arg, j);
	return (extract_var_name(arg, j, end));
}

static int	handle_null_variable(t_cmd_token **token, int i, int j, char **env, char **start)
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

char	*start_of_env(char *arg)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (arg[i] != '$')
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ptr[j] = arg[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*extract_var_name(char *arg, int start, int end)
{
	char	*ptr;
	int		k;
	int		j;

	ptr = malloc((end - start) * sizeof(char));
	if (!ptr)
		return (NULL);
	k = 0;
	j = start + 1;
	while (j < end)
	{
		ptr[k] = arg[j];
		k++;
		j++;
	}
	ptr[k] = '\0';
	return (ptr);
}
