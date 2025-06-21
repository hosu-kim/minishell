/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:21:03 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 12:15:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	process_token_args(t_cmd_token *token, int exit_status)
{
	int	i;
	int	j;

	i = 0;
	while (token->cmd_with_args && token->cmd_with_args[i] != NULL)
	{
		j = 0;
		while (token->cmd_with_args[i][j] != '$'
				&& token->cmd_with_args[i][j] != '\0'
				&& (token->arg_types[i] == UNQUOTED
				|| token->arg_types[i] == DQUOTED))
			j++;
		if (token->cmd_with_args[i][j] == '$' && token->arg_types[i] != QUOTED)
		{
			if (token->cmd_with_args[i][j + 1] == '?'
				|| token->cmd_with_args[i][j + 1] == '$' ||
				is_valid_var_char(token->cmd_with_args[i][j + 1]))
			{
				if (make_env(&token, i, j, exit_status) == 1)
					continue ;
			}
		}
		i++;
	}
}

static int	skip_var_name(char *arg, int j)
{
	j++;
	if (arg[j] == '?' || arg[j] == '$')
		j++;
	else
	{
		while ((arg[j] >= '0' && arg[j] <= '9')
			|| (arg[j] >= 'a' && arg[j] <= 'z')
			|| (arg[j] >= 'A' && arg[j] <= 'Z') || arg[j] == '_')
			j++;
	}
	return (j);
}

static char	*create_updated_string(char *start, char *var, char *arg, int j)
{
	char	*ptr;
	int		i;
	int		l;
	int		m;

	i = ft_strlen(start) + ft_strlen(var) + (ft_strlen(arg) - j);
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	l = -1;
	while (++l < i && start[l])
		ptr[l] = start[l];
	m = 0;
	while (l < i && var[m])
		ptr[l++] = var[m++];
	while (l < i && arg[j])
		ptr[l++] = arg[j++];
	ptr[l] = '\0';
	return (ptr);
}

void	update_token(char **arg, char *start, int j)
{
	int		new_j;
	char	*ptr;

	new_j = skip_var_name(*arg, j);
	ptr = create_updated_string(start, "", *arg, new_j);
	if (!ptr)
		return ;
	free(*arg);
	*arg = ptr;
}

void	remake_token(char **arg, char *start, char *var, int j)
{
	int		new_j;
	char	*ptr;

	new_j = skip_var_name(*arg, j);
	ptr = create_updated_string(start, var, *arg, new_j);
	if (!ptr)
		return ;
	free(*arg);
	*arg = ptr;
}
