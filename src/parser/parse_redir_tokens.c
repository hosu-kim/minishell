/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:33:51 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 16:56:18 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_type(t_token ***lex_token)
{
	if ((**lex_token) && (**lex_token)->type != T_PIPE
		&& ((**lex_token)->type == T_REDIR_IN
			|| (**lex_token)->type == T_REDIR_OUT
			|| (**lex_token)->type == T_REDIR_APPEND
			|| (**lex_token)->type == T_HEREDOC))
		return (1);
	return (0);
}

static void	check_redir_type(t_token ***lex_token, t_redirection *new_redir)
{
	new_redir->type = (**lex_token)->type;
}

static void	make_redirection_list(t_token ***lex_token, t_cmd_token *new_token,
		t_redirection *new_redir, t_redirection **current)
{
	if ((**lex_token)->type == T_REDIR_IN || (**lex_token)->type == T_HEREDOC)
		add_to_input_list(new_token, new_redir, current);
	else if ((**lex_token)->type == T_REDIR_OUT
		|| (**lex_token)->type == T_REDIR_APPEND)
		add_to_output_list(new_token, new_redir, current);
	add_to_all_redirs(new_token, new_redir);
}

static void	move_lex_token(t_token ***lex_token)
{
	if ((**lex_token))
		(**lex_token) = (**lex_token)->next;
	if ((**lex_token))
		(**lex_token) = (**lex_token)->next;
}

int	is_redirection_token(t_token **lex_token, t_cmd_token *new_token)
{
	t_redirection	*new_redir;
	t_redirection	*current;
	static int		order_counter = 0;

	while (check_type(&lex_token))
	{
		if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
				&& (*lex_token)->next->type != T_Q_WORD
				&& (*lex_token)->next->type != T_D_Q_WORD))
			return (printf("Syntax error\n"), 1);
		new_redir = malloc(sizeof(t_redirection));
		if (!new_redir)
			return (1);
		new_redir->target_types = get_args_type((*lex_token)->next->type);
		new_redir->order = order_counter++;
		check_redir_type(&lex_token, new_redir);
		if ((*lex_token)->next)
			new_redir->target = ft_strdup((*lex_token)->next->value);
		else
			new_redir->target = NULL;
		new_redir->next = NULL;
		make_redirection_list(&lex_token, new_token, new_redir, &current);
		move_lex_token(&lex_token);
	}
	return (0);
}
