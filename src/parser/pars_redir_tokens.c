/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:33:51 by jakand            #+#    #+#             */
/*   Updated: 2025/05/25 13:35:06 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int     check_type(t_token ***lex_token)
{
    if((**lex_token) && (**lex_token)->type != T_PIPE
        && ((**lex_token)->type == T_REDIR_IN
        || (**lex_token)->type == T_REDIR_OUT
        || (**lex_token)->type == T_REDIR_APPEND
        || (**lex_token)->type == T_HEREDOC))
        return (1);
    return (0);
}

void    check_redir_type(t_token ***lex_token, t_redirection *new_redir)
{
    if ((**lex_token)->type == T_REDIR_IN)
        new_redir->type = TOK_INPUT;
    if ((**lex_token)->type == T_REDIR_OUT)
        new_redir->type = TOK_OUTPUT;
    if ((**lex_token)->type == T_REDIR_APPEND)
        new_redir->type = TOK_APPEND;
    if ((**lex_token)->type == T_HEREDOC)
        new_redir->type = TOK_HEREDOC;
}

void    make_redirection_list(t_token ***lex_token, t_command *new_token,
        t_redirection *new_redir, t_redirection **current)
{
    if ((**lex_token)->type == T_REDIR_IN || (**lex_token)->type == T_HEREDOC)
    {
        if (!new_token->input_redir)
            new_token->input_redir = new_redir;
        else
        {
            (*current) = new_token->input_redir;
            while ((*current)->next)
                (*current) = (*current)->next;
            (*current)->next = new_redir;
        }
    }
        if ((**lex_token)->type == T_REDIR_OUT
            || (**lex_token)->type == T_REDIR_APPEND)
        {
        if (!new_token->output_redir)
            new_token->output_redir = new_redir;
        else
        {
            (*current) = new_token->output_redir;
            while ((*current)->next)
                (*current) = (*current)->next;
            (*current)->next = new_redir;
        }
    }
}

int     redir_tok(t_token **lex_token, t_command *new_token)
{
    t_redirection *new_redir;
    t_redirection *current;
    
    while (check_type(&lex_token))
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
            && (*lex_token)->next->type != T_Q_WORD
            && (*lex_token)->next->type != T_D_Q_WORD))
            return (printf("Syntax error\n"), 1);
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (1);
        check_redir_type(&lex_token, new_redir);
        if ((*lex_token)->next)
            new_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_redir->target = NULL;
        new_redir->next = NULL;
        make_redirection_list(&lex_token, new_token, new_redir, &current);
        if ((*lex_token))
            (*lex_token) = (*lex_token)->next;
        if ((*lex_token))
            (*lex_token) = (*lex_token)->next;
    }
    return (0);
}
