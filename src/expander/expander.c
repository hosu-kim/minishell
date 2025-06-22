/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 21:08:54 by jaandras         ###   ########.fr       */
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

static char	*str_cpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	get_num_len(int n)
{
	int	num_len;

	num_len = 0;
	if (n <= 0)
		num_len++;
	while (n)
	{
		n /= 10;
		num_len++;
	}
	return (num_len);
}

static char	*convert_number(int n, int num_len)
{
	char	*ptr;
	int		i;

	i = num_len - 1;
	ptr = (char *)malloc((num_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[num_len] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
	}
	while (n)
	{
		ptr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		num_len;
	char	*result;

	if (n == -2147483648)
	{
		result = malloc(12 * sizeof(char));
		if (!result)
			return (NULL);
		return (str_cpy(result, "-2147483648"));
	}
	num_len = get_num_len(n);
	result = convert_number(n, num_len);
	return (result);
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
