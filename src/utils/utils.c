/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:37:14 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 13:02:58 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_valid_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
}

void	free_var(char **env, char **var)
{
	if (*env)
		free(*env);
	if (*var)
		free(*var);
}

/**
 * @brief Skips leading whitespaces by advancing the input pointer.
 */
int	skip_whitespaces(const char **input)
{
	while (**input == ' ' || (**input >= '\t' && **input <= '\r'))
		(*input)++;
	if (**input == '\0')
		return (FAILURE);
	return (SUCCESS);
}
