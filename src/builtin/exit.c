/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:29:24 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 13:28:59 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (NO);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (NO);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (NO);
		i++;
	}
	return (YES);
}

static int	check_special_cases(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == '-' && arg[1] == '"')
		return (1);
	if (arg[0] == '+' && arg[1] == '"')
		return (1);
	return (0);
}

static int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	builtin_exit(char **args)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (check_special_cases(args[1]))
	{
		write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
		exit(2);
	}
	if (!is_numeric(args[1]))
	{
		write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
		exit(2);
	}
	if (args[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return (FAILURE);
	}
	exit_code = ft_atoi(args[1]);
	exit(exit_code % 256);
}
