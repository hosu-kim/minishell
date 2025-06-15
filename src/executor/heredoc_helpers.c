/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:02:26 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/15 15:27:11 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static ssize_t	readline_heredoc(char **line, size_t *sz)
{
	ssize_t	n;

	if (write(STDOUT_FILENO, "> ", 2) < 0)
		perror("prompt");
	n = getline(line, sz, stdin);
	if (n > 0 && (*line)[n -1] == '\n')
		(*line)[n - 1] = '\0';
	return (n);
}

static void	process_unquoted(int fd, char *line)
{
	t_cmd_token	tmp;
	char	*dup = strdup(line);
	char	*args[2] = { dup, NULL };
	int		types[2] = { UNQUOTED, 0};

	tmp.cmd_with_args = args;
	tmp.arg_types = types;
	tmp.input_redirs = NULL;
	tmp.output_redirs = NULL;
	tmp.has_pipe = 0;
	tmp.next_cmd_token = NULL;
	expand_token(&tmp);
	write(fd, tmp.cmd_with_args[0], strlen(tmp.cmd_with_args[0]));
	write(fd, "\n", 1);
	free(tmp.cmd_with_args[0]);
	free(dup);
}

static void	process_quoted(int fd, char *line)
{
	write(fd, line, strlen(line));
	wirte(fd, "\n", 1);
}

int	write_heredoc_lines(int wfd, t_redirection *redir)
{
	char	*line = NULL;
	size_t	sz = 0;
	ssize_t	n;

	while ((n = readline_heredoc(&line, &sz)) > 0)
	{
		if (strcmp(line, redir->target) == 0)
			break ;
		if (redir->target_types == UNQUOTED)
			process_unquoted(wfd, line);
		else
			process_quoted(wfd, line);
	}
	free(line);
	return (0);
}

int	attach_pipe_to_stdin(int rfd)
{
	if (dup2(rfd, STDIN_FILENO) < 0)
		return (perror("dub2 heredoc"), close(rfd), 1);
	close(rfd);
	return (0);
}