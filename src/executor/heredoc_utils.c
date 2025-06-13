/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:24:42 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/13 21:44:33 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	initialize_heredoc_temp_file(t_redirection *redir,
								int *expand_variables,
								const char *filename)
{
	int	fd;

	if (redir->target_types == 1)
		*expand_variables = 1;
	else
		*expand_variables = 0;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("filename");
		return (-1);
	}
	return (fd);
}

static int	write_input_to_temp_file(int fd, char *line_to_write)
{
	if (write(fd, line_to_write, ft_strlen(line_to_write)) == -1)
	{
		perror("heredoc: write to temp file failed");
		return (1);
	}
	if (write(fd, "\n", 1) == -1)
	{
		perror("heredoc: write newline to temp file failed");
		return (1);
	}
	return (0);
}

static int	heredoc_cleanup(const char *perror_msg,
							int fd_to_close,
							char *input_to_free,
							char *processed_to_free)
{
	perror(perror_msg);
	if (input_to_free)
		free(input_to_free);
	if (processed_to_free)
		free(processed_to_free);
	close(fd_to_close);
	return (1);
}

int	process_and_write_heredoc_input(int fd, 
									t_redirection *redir,
									int expand_variables)
{
	char	*user_input;
	char	*processed_input;
	char	*delimiter;

	delimiter = redir->target;
	(void)expand_variables;
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
		processed_input = ft_strdup(user_input);
		if (!processed_input)
			return (heredoc_cleanup("Error", fd, user_input, NULL));
		if (write_input_to_temp_file(fd, processed_input) != 0)
			return (heredoc_cleanup("Error", fd, user_input, processed_input));
		free(processed_input);
		free(user_input);
	}
	return (0);
}
