/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:02:26 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 01:29:02 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * @brief Prints a heredoc prompt "> ", reads one line from stdin, strips '\n'.
 * @param line Pointer to a buffer holding the input line. If *line_buffer is
 * 			   NULL or too small, getline() reallocates it.
 * @param size Pointer to a size_t with the capacity of *line_buffer. After
 * 			   getline(), it is updated to reflect the buffer's allocated size.
 * @return On success, returns the number of characters read
 * 		   (excluding the stripped newline).
 * 		   On EOF or error, returns -1.
 */
static ssize_t	readline_heredoc(char **line_buffer, size_t *line_buffer_size)
{
	ssize_t	bytes_read;

	if (write(STDOUT_FILENO, "> ", 2) < 0)
		perror("prompt");
	bytes_read = getline(line_buffer, line_buffer_size, stdin);
	if (bytes_read > 0 && (*line_buffer)[bytes_read - 1] == '\n')
		(*line_buffer)[bytes_read - 1] = '\0';
	return (bytes_read);
}

static void	process_unquoted(int std_fd, char *line)
{
	t_cmd_token	temp;
	char		*dup = ft_strdup(line);
	char		*args[2] = { dup, NULL };
	t_arg_type	types[2] = { UNQUOTED, 0 };

	temp.cmd_with_args = args;
	temp.arg_types = types;
	temp.input_redirs = NULL;
	temp.output_redirs = NULL;
	temp.has_pipe = 0;
	temp.next_cmd_token = NULL;
	expand_token(&temp, 0);
	write(std_fd, temp.cmd_with_args[0], strlen(temp.cmd_with_args[0]));
	write(std_fd, "\n", 1);
	free(temp.cmd_with_args[0]);
	free(dup);
}

static void	process_quoted(int fd, char *line)
{
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
}

int	write_heredoc_lines(int out_fd, t_redirection *redir)
{
	char	*line_buffer = NULL;
	size_t	buffer_size = 0;
	ssize_t	bytes_read;

	while ((bytes_read = readline_heredoc(&line_buffer, &buffer_size)) > 0)
	{
		if (ft_strcmp(line_buffer, redir->target) == 0)
			break ;
		if (redir->target_types == UNQUOTED)
			process_unquoted(out_fd, line_buffer);
		else
			process_quoted(out_fd, line_buffer);
	}
	free(line_buffer);
	return (0);
}

int	redirect_stdin_from_fd(int in_fd)
{
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 heredoc");
		close(in_fd);
		return (1);
	}
	close(in_fd);
	return (0);
}
