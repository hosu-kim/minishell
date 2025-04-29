/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:52:07 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/29 19:55:04 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "readline_wrapper.h"

/**
 * Prompt the user and return the entered line.
 * If EOF is received (e.g., Ctrl-D), returns NULL.
 * Non-empty lines are saved in the history list.
 * Caller must free the returned buffer.
 */
char	*get_input_line(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line == NULL)
		return (NULL);
	if (*line != '\0')
		add_history(line);
	return (line);
}