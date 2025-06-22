/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:00:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 16:56:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*initialize_parser(t_token *start, t_cmd_token **cmd_start,
		t_cmd_token **current, t_cmd_token **new_token)
{
	(*cmd_start) = NULL;
	(*current) = NULL;
	(*new_token) = NULL;
	return (start);
}
