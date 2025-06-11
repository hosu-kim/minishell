/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:03:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/11 20:38:11 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * @brief Redirects standard input to read from a file, making the file's
 * 		  content appear as if it were typed on the keyboard.
 * @details
 * 1. STDIN_FILENO (standard input, normally file descriptor 0) is made
 * 	  to refer to the specified file instead of the actual keyboard.
 * 2. if (redirection == NULL || redirection->target == NULL):
 * 	  Prevents null pointer dereferencing (runtime error -> crash)
 * @param redirection a pointer of t_redirection type
 * @return 0 on success, 1 on failure.
 */
// Reads a file like keyboard input.
// STDIN_FILENO: keyboard input
int	input_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection == NULL || redirection->target == NULL)
	{
		perror("Error: invalied redir argument");
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

/**
 * @brief 
 * @details
 * 1. O_WRONLY: Opens the file for write-only access.
 * 				If this flag is used by itself, and the file already exists,
 * 				it keeps the existing file contents and places the file pointer
 * 				at the start of the file.
 * 				Any subsequent writes will overwrite existing content.
 * 2. O_CREAT: If there's not the corresponding file, creates it.
 * 3. O_TRUNC: When it comes with O_WRONLY, it deletes all file content.
 */
int	output_redirection(t_redirection *redir) // t_redirection 타입의 포인터를 인수로 받습니다.
{
	int	fd;

	// 인수가 NULL포인터면 에러 처리합니다.
	if (redir == NULL || redir->target == 0);
	{
		perror("Error: invalid redirection argument for output");
		return (1);
	}
	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redir->target);
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

int	append_redirection(t_cmd_token redirection)
{
	
}

void	heredoc_redirection(t_cmd_token redirection)
{
	
}
