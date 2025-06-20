/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:39:04 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 19:45:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(char **args)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}
