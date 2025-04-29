/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_wrapper.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:47:26 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/29 19:56:58 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_WRAPPER_H
# define READLINE_WRAPPER_H
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
/**
 * Display the given prompt and read a line of input from the user.
 * Returns:
 *   - A heap-allocated string containing the user's input 
 *     (excluding the newline).
 *   - NULL if end-of-file (Ctrl-D) is encountered.
 * Side effects:
 *   - Non-empty input is added to the readline history.
 * Ownership:
 *   - Caller is responsible for freeing the returned string.
 */
char	*get_input_line(const char *prompt);

#endif
