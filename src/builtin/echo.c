/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:22:57 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 14:01:35 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (NO);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (NO);
		i++;
	}
	return (YES);
}

static void	print_args(char **args, int start_index, int newline)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	if (!args[1])
	{
		printf("\n");
		return (SUCCESS);
	}
	newline = 1;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	print_args(args, i, newline);
	return (SUCCESS);
}
