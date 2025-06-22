/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:06:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 17:51:42 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	process_export_arg(char *arg, char ***env)
{
	char	*address_of_equal_sign;

	address_of_equal_sign = ft_strchr(arg, '=');
	if (address_of_equal_sign)
		return (handle_export_with_value(arg, address_of_equal_sign, env));
	else
		return (handle_export_without_value(arg, env));
}

int	builtin_export(char **args, char ***env)
{
	int	i;
	int	exit_code;

	if (!args[1])
		return (builtin_env(*env));
	exit_code = 0;
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env) == 1)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
