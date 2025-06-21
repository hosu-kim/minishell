/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:29:59 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 12:22:13 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_args(t_cmd_token *start)
{
	int	i;

	i = 0;
	if (start->cmd_with_args)
	{
		i = 0;
		while (start->cmd_with_args[i])
		{
			free(start->cmd_with_args[i]);
			i++;
		}
		free(start->cmd_with_args);
	}
	if (start->arg_types)
		free(start->arg_types);
}

void	free_input_redir(t_redirection *redir)
{
	t_redirection	*temp;

	while (redir)
	{
		temp = redir->next;
		free(redir->target);
		free(redir);
		redir = temp;
	}
}

void	free_output_redir(t_redirection *redir)
{
	t_redirection	*temp;

	while (redir)
	{
		temp = redir->next;
		free(redir->target);
		free(redir);
		redir = temp;
	}
}

void	free_cmd_tokens(t_cmd_token *start)
{
	t_cmd_token		*cmd;
	t_redirection	*redir;

	if (!start)
		return ;
	cmd = start;
	while (start)
	{
		cmd = start->next_cmd_token;
		free_args(start);
		redir = start->input_redirs;
		if (redir)
			free_input_redir(redir);
		redir = start->output_redirs;
		if (redir)
			free_output_redir(redir);
		free(start);
		start = cmd;
	}
}
