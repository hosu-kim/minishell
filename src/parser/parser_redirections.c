/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:00:00 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 16:56:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_input_redirection(t_cmd_token *token, t_redirection *redir)
{
	t_redirection	*current;

	if (!token->input_redirs)
		token->input_redirs = redir;
	else
	{
		current = token->input_redirs;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

static void	add_output_redirection(t_cmd_token *token, t_redirection *redir)
{
	t_redirection	*current;

	if (!token->output_redirs)
		token->output_redirs = redir;
	else
	{
		current = token->output_redirs;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

static int	create_redirection(t_token **lex_token, t_redirection **new_redir,
		int order)
{
	*new_redir = malloc(sizeof(t_redirection));
	if (!(*new_redir))
		return (1);
	(*new_redir)->type = (*lex_token)->type;
	(*new_redir)->target_types = get_args_type((*lex_token)->next->type);
	(*new_redir)->target = ft_strdup((*lex_token)->next->value);
	(*new_redir)->order = order;
	(*new_redir)->next = NULL;
	return (0);
}

int	process_redirection_at_position(t_token **lex_token, t_cmd_token *new_token)
{
	t_redirection	*new_redir;
	t_redirection	*copy;
	static int		global_order = 0;

	if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
			&& (*lex_token)->next->type != T_Q_WORD
			&& (*lex_token)->next->type != T_D_Q_WORD))
		return (printf("Syntax error\n"), 1);
	if (create_redirection(lex_token, &new_redir, global_order++))
		return (1);
	if ((*lex_token)->type == T_REDIR_IN || (*lex_token)->type == T_HEREDOC)
		add_input_redirection(new_token, new_redir);
	else if ((*lex_token)->type == T_REDIR_OUT
		|| (*lex_token)->type == T_REDIR_APPEND)
		add_output_redirection(new_token, new_redir);
	copy = create_redir_copy(new_redir);
	if (copy)
		add_redir_to_all_list(new_token, copy);
	*lex_token = (*lex_token)->next;
	*lex_token = (*lex_token)->next;
	return (0);
}
