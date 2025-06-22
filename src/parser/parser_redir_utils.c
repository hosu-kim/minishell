/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:47:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 16:56:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_to_input_list(t_cmd_token *new_token, t_redirection *new_redir,
		t_redirection **current)
{
	if (!new_token->input_redirs)
		new_token->input_redirs = new_redir;
	else
	{
		(*current) = new_token->input_redirs;
		while ((*current)->next)
			(*current) = (*current)->next;
		(*current)->next = new_redir;
	}
}

void	add_to_output_list(t_cmd_token *new_token, t_redirection *new_redir,
		t_redirection **current)
{
	if (!new_token->output_redirs)
		new_token->output_redirs = new_redir;
	else
	{
		(*current) = new_token->output_redirs;
		while ((*current)->next)
			(*current) = (*current)->next;
		(*current)->next = new_redir;
	}
}

void	add_to_all_redirs(t_cmd_token *new_token, t_redirection *new_redir)
{
	t_redirection	*all_current;
	t_redirection	*all_copy;

	all_copy = malloc(sizeof(t_redirection));
	if (!all_copy)
		return ;
	all_copy->type = new_redir->type;
	all_copy->target = ft_strdup(new_redir->target);
	all_copy->target_types = new_redir->target_types;
	all_copy->order = new_redir->order;
	all_copy->next = NULL;
	if (!new_token->all_redirs)
		new_token->all_redirs = all_copy;
	else
	{
		all_current = new_token->all_redirs;
		while (all_current->next)
			all_current = all_current->next;
		all_current->next = all_copy;
	}
}

t_redirection	*create_redir_copy(t_redirection *original)
{
	t_redirection	*copy;

	copy = malloc(sizeof(t_redirection));
	if (!copy)
		return (NULL);
	copy->type = original->type;
	copy->target = ft_strdup(original->target);
	copy->target_types = original->target_types;
	copy->order = original->order;
	copy->next = NULL;
	return (copy);
}

void	add_redir_to_all_list(t_cmd_token *token, t_redirection *copy)
{
	t_redirection	*current;

	if (!token->all_redirs)
		token->all_redirs = copy;
	else
	{
		current = token->all_redirs;
		while (current->next)
			current = current->next;
		current->next = copy;
	}
}
