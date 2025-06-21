/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:21:03 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 02:08:06 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

void	process_token_args(t_cmd_token *token, int exit_status)
{
	int	i;
	int	j;

	i = 0;
	while (token->cmd_with_args && token->cmd_with_args[i] != NULL)
	{
		j = 0;
		while (token->cmd_with_args[i][j] != '$' && token->cmd_with_args[i][j] != '\0'
				&& (token->arg_types[i] == UNQUOTED || token->arg_types[i] == DQUOTED))
			j++;
		if (token->cmd_with_args[i][j] == '$' && token->arg_types[i] != QUOTED)
		{
			if (token->cmd_with_args[i][j + 1] == '?' || token->cmd_with_args[i][j + 1] == '$' ||
				is_valid_var_char(token->cmd_with_args[i][j + 1]))
			{
				if (make_env(&token, i, j, exit_status) == 1)
					continue ;
			}
		}
		i++;
	}
}

void	update_token(char **arg, char *start, int j)
{
	int		i;
	int		l;
	char	*ptr;

	j++;
	if ((*arg)[j] == '?' || (*arg)[j] == '$')
		j++;
	else
	{
		while (((*arg)[j] >= '0' && (*arg)[j] <= '9')
			|| ((*arg)[j] >= 'a' && (*arg)[j] <= 'z')
			|| ((*arg)[j] >= 'A' && (*arg)[j] <= 'Z') || (*arg)[j] == '_')
			j++;
	}
	i = ft_strlen(start) + (ft_strlen(*arg) - j);
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return ;
	l = 0;
	while (l < i && start[l])
	{
		ptr[l] = start[l];
		l++;
	}
	while (l < i && (*arg)[j])
		ptr[l++] = (*arg)[j++];
	ptr[l] = '\0';
	free((*arg));
	(*arg) = ptr;
}

void	remake_token(char **arg, char *start, char *var, int j)
{
	int		i;
	int		l;
	int		m;
	char	*ptr;

	j++;
	if ((*arg)[j] == '?' || (*arg)[j] == '$')
		j++;
	else
	{
		while (((*arg)[j] >= '0' && (*arg)[j] <= '9')
			|| ((*arg)[j] >= 'a' && (*arg)[j] <= 'z')
			|| ((*arg)[j] >= 'A' && (*arg)[j] <= 'Z') || (*arg)[j] == '_')
			j++;
	}
	i = ft_strlen(start) + ft_strlen(var) + (ft_strlen(*arg) - j);
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return ;
	l = -1;
	while (++l < i && start[l])
		ptr[l] = start[l];
	m = 0;
	while (l < i && var[m])
		ptr[l++] = var[m++];
	while (l < i && (*arg)[j])
		ptr[l++] = (*arg)[j++];
	ptr[l] = '\0';
	free((*arg));
	(*arg) = ptr;
}
