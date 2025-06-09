/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/09 15:08:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Initializes t_command pointers to NULL and returns lex_start, the initial token from the lexer.
t_token	*initialize_t_command_pointers(t_token *lex_start, t_cmd_token **start,
				t_cmd_token **current, t_cmd_token **new_token)
{
	(*start) = NULL;
	(*current) = NULL;
	(*new_token) = NULL;
	return (lex_start);
}

void	*initialize_new_token_members(t_cmd_token *new_token)
{
	new_token->cmd_with_args = NULL;
	new_token->argc = 0;
	new_token->arg_types = 0;
	new_token->input_redirs = NULL;
	new_token->output_redirs = NULL;
	new_token->has_pipe = 0;
	new_token->next_cmd_token = NULL;
	return (new_token);
}

void	make_token_list(t_cmd_token **start, t_cmd_token *new_token,
		t_cmd_token **current)
{
	if (!(*start))
		(*start) = new_token;
	else
		(*current)->next_cmd_token = new_token;
	(*current) = new_token;
}

t_cmd_token	*parser(t_token *lex_start)
{
	t_token		*lexed_token;
	t_cmd_token	*start;
	t_cmd_token	*current;
	t_cmd_token	*new_parsed_token;

	lexed_token = initialize_t_command_pointers(lex_start, &start, &current, &new_parsed_token);
	while (lexed_token)
	{
		new_parsed_token = malloc(sizeof(t_cmd_token));
		if (!new_parsed_token)
			return (free_command(start), NULL);
		initialize_new_token_members(new_parsed_token);
		if (is_pipe_token(&lexed_token, new_parsed_token)
			|| is_text_token(lexed_token, &lexed_token, new_parsed_token)
			|| is_redirection_token(&lexed_token, new_parsed_token))
		{
			if (new_parsed_token)
				free_command(new_parsed_token);
			if (start)
				free_command(start);
			return (NULL);
		}
		make_token_list(&start, new_parsed_token, &current);
	}
	return (start);
}



// int     input_tok(t_token **lex_token, t_command *new_token)
// {
//     t_redirection *new_redir;
//     t_redirection *current;
	
//     if (*lex_token && ((*lex_token)->type == T_REDIR_IN))
//     {
//         if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
//             && (*lex_token)->next->type != T_Q_WORD
//             && (*lex_token)->next->type != T_D_Q_WORD))
//             return (printf("Syntax error\n"), 1);
		
//         new_redir = malloc(sizeof(t_redirection));
//         if (!new_redir)
//             return (1);
		
//         new_redir->type = TOK_INPUT;
//         if ((*lex_token)->next)
//             new_redir->target = ft_strdup((*lex_token)->next->value);
//         else
//             new_redir->target = NULL;
//         new_redir->next = NULL;
		
//         // Chain the redirection instead of overwriting
//         if (!new_token->input_redir)
//         {
//             new_token->input_redir = new_redir;
//         }
//         else
//         {
//             current = new_token->input_redir;
//             while (current->next)
//                 current = current->next;
//             current->next = new_redir;
//         }
//     }
//     else
//         return (0);
//     if ((*lex_token))
//         (*lex_token) = (*lex_token)->next;
//     if ((*lex_token))
//         (*lex_token) = (*lex_token)->next;
//     return (0);
// }

// int    heredoc_tok(t_token **lex_token, t_command *new_token)
// {
//     t_redirection *new_redir;
//     t_redirection *current;
	
//     if ((*lex_token) && (*lex_token)->type == T_HEREDOC)
//     {
//         if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
//             && (*lex_token)->next->type != T_Q_WORD
//             && (*lex_token)->next->type != T_D_Q_WORD))
//             return (printf("Syntax error\n"), 1);
		
//         new_redir = malloc(sizeof(t_redirection));
//         if (!new_redir)
//             return (1);
		
//         new_redir->type = TOK_HEREDOC;
//         if ((*lex_token)->next)
//             new_redir->target = ft_strdup((*lex_token)->next->value);
//         else
//             new_redir->target = NULL;
//         new_redir->next = NULL;
		
//         // Chain the redirection instead of overwriting
//         if (!new_token->input_redir)
//         {
//             new_token->input_redir = new_redir;
//         }
//         else
//         {
//             current = new_token->input_redir;
//             while (current->next)
//                 current = current->next;
//             current->next = new_redir;
//         }
//     }
//     else
//         return (0);
//     if ((*lex_token))
//         (*lex_token) = (*lex_token)->next;
//     if ((*lex_token))
//         (*lex_token) = (*lex_token)->next;
//     return (0);
// }

// int    output_tok(t_token **lex_token, t_command *new_token)
// {
//     t_redirection *new_redir;
//     t_redirection *current;
	
//     if ((*lex_token) && (*lex_token)->type == T_REDIR_OUT)
//     {
//         if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
//             && (*lex_token)->next->type != T_Q_WORD
//             && (*lex_token)->next->type != T_D_Q_WORD))
//             return (printf("Syntax error\n"), 1);
		
//         new_redir = malloc(sizeof(t_redirection));
//         if (!new_redir)
//             return (1);
		
//         new_redir->type = TOK_OUTPUT;
//         if ((*lex_token)->next)
//             new_redir->target = ft_strdup((*lex_token)->next->value);
//         else
//             new_redir->target = NULL;
//         new_redir->next = NULL;
		
//         // Chain the redirection instead of overwriting
//         if (!new_token->output_redir)
//         {
//             new_token->output_redir = new_redir;
//         }
//         else
//         {
//             current = new_token->output_redir;
//             while (current->next)
//                 current = current->next;
//             current->next = new_redir;
//         }
//     }
//     else
//         return (0);
//     if ((*lex_token))
//         (*lex_token) = (*lex_token)->next;
//     if ((*lex_token))
//         (*lex_token) = (*lex_token)->next;
//     return (0);
// }
