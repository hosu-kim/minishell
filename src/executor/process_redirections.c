/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:03:22 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/13 19:55:31 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * @brief Redirects standard input to read from a file, making the file's
 * 		  content appear as if it were typed on the keyboard.
 * @note
 * 1. STDIN_FILENO (standard input, normally file descriptor 0) is made
 * 	  to refer to the specified file instead of the actual keyboard.
 * 2. if (redirection == NULL || redirection->target == NULL):
 * 	  Prevents null pointer dereferencing (runtime error -> crash)
 * @param redir a pointer of t_redirection type
 * @return 0 on success, 1 on failure.
 */
// Reads a file like keyboard input.
// STDIN_FILENO: keyboard input
int	input_redirection(t_redirection *redir)
{
	int	fd;

	if (redir == NULL || redir->target == NULL)
	{
		perror("Error: invalied redir argument");
		return (1);
	}
	fd = open(redir->target, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->target);
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
	return (fd);
}

/**
 * @brief Redirects standard output to a specified file.
 * @note
 * 1. O_WRONLY: Opens the file for write-only access.
 * 				If this flag is used by itself, and the file already exists,
 * 				it keeps the existing file contents and places the file pointer
 * 				at the start of the file.
 * 				Any subsequent writes will overwrite existing content.
 * 2. O_CREAT: If there's not the corresponding file, creates it.
 * 3. O_TRUNC: When it comes with O_WRONLY, it deletes all file content.
 * 4. 0644: File psermission setup
 * 5. STDOUT_FILENO: Standard output (Basically Console output)
 * @param redir a pointer of t_redirection type
 * @return 0 on success, 1 on failure
 */
int	output_redirection(t_redirection *redir)
{
	int	fd;

	if (redir == NULL || redir->target == NULL)
	{
		perror("Error: invalid redirection argument");
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
		perror("Failed in close(fd)");
		return (1);
	}
	return (0);
}

/**
 * @brief Redirects standard output to a specified file in append mode.
 * @note O_APPEND: Writes data to the end of the file, appending if it exists.
 * @param redir a pointer of t_redirection type
 * @return 0 on success, 1 on failure
 */
int	append_redirection(t_redirection *redir)
{
	int	fd;
	
	if (redir == NULL || redir->target == NULL)
	{
		perror("Error: Invalid redir argument");
		return (1);
	}
	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
		perror("Failed in close(fd)");
		return (1);
	}
	return (0);
}

/**
 * 1. 임시 텍스트 파일 생성
 * 2.  키보드 입력을 한 줄씩 받아 임시 파일에 저장.
 * 3. 입력된 줄이 지정된 delimiter와 일치하는지 매번 확인합니다.
 * 4. Delimiter가 인식되면, 임시 파일에 저장된 내용을 콘솔에 출력.
 * 5. 임시 파일을 삭제.
 * # strcmp implement.
 */
int	heredoc_redirection(t_redirection *redir)
{
	int		fd;
	char	*delimiter = redir->target;
	char	*user_input;
	char	*processed_input;
	ssize_t	bytes_written;
	int		expand_variables;

	if (redir->target_types == 1)
		expand_variables = 1;
	else
		expand_variables = 0;

	fd = open(".minishell_heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Open heredoc temp file failed");
		return (1);
	}
	while (1)
	{
		printf("%s", delimiter);
		user_input = readline("> ");
		if (user_input == NULL)
			break ;
		if (ft_strcmp(user_input, delimiter) == 0)
		{
			free(user_input);
			break ;
		}
		if (expand_variables)
		{
			processed_input = ft_strdup(user_input);
			if (!processed_input)
			{
				perror("Memory allocation failed for processed_input");
				free(user_input);
				close(fd);
				return (1);
			}
		}
		else
		{
			processed_input = ft_strdup(user_input);
			if (!processed_input)
			{
				perror("Memory allocation failed for process_input");
				free(user_input);
				close(fd);
				return (1);
			}
		}
		bytes_written = write(fd, user_input, ft_strlen(user_input));
		if (bytes_written == -1)
		{
			perror("write to heredoc temp file failed");
			free(processed_input);
			free(user_input);
			close(fd);
			return (1);
		}
		bytes_written = write(fd, "\n", 1);
		if (bytes_written == -1)
		{
			perror("write newline to heredoc temp file failed");
			free(processed_input);
			free(user_input);
			close(fd);
			return (1);
		}
		free(processed_input);
		free(user_input);
	}

	if (close(fd) == -1)
	{
		perror("close heredoc temp file failed");
		return (1);
	}	
	return (1);
}
