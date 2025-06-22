/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:30:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 15:26:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include <errno.h>

static void	check_file_status(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			perror(path);
			exit(126);
		}
		if (access(path, X_OK) != 0)
		{
			perror(path);
			exit(126);
		}
	}
	else
	{
		perror(path);
		exit(127);
	}
}

void	execute_with_path(char **argv, char **envp)
{
	check_file_status(argv[0]);
	execve(argv[0], argv, envp);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}
