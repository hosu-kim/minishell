/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:26:04 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 21:28:09 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tokenization_error(void)
{
	if (errno != 0)
		perror("minishell");
}

void	handle_parsing_error(t_token *tokens)
{
	ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	free_tokens(tokens);
}
