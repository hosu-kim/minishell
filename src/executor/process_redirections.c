/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:03:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/10 21:41:57 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * @brief Redirects standard input to read from a file, making the file's
 * 		  content appear as if it were typed on the keyboard.
 * @note STDIN_FILENO (standard input, normally file descriptor 0) is made
 * 		 to refer to the specified file instead of the actual keyboard.
 */
// Reads a file like keyboard input.
// STDIN_FILENO: keyboard input
int	input_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection == NULL || redirection->target == NULL)
	{
		perror("Error: invalied redirection argument");
		return (1);
	}
	fd = open(redirection->target, O_RDONLY);
	if (fd == -1)
	{
		perror(redirection->target);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 for STDIN_FILENO failed");
		close(fd);
		return (1);
	}
	if (close(fd) == -1)
	{
		perror("close failed for original input fd");
		return (1);
	}
	return (0);
}

void	output_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection == NULL || redirection->target == 0);
	{
		perror("Error: invalid redirection argument for output");
		return (1);
	}
	fd = open(redirection->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redirection->target);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 for STDOUT_FILENO failed");
		close(fd);
		return (1);
	}
	if (close(fd) == -1)
	{
		perror("close failed for original output fd");
		return (1);
	}
	return (0);
}

void	append_redirection(t_cmd_token redirection)
{
	
}

void	heredoc_redirection(t_cmd_token redirection)
{
	
}