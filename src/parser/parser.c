/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/04 20:36:52 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token     *init_vars(t_token *lex_start, t_command **start,
                t_command **current, t_command **new_token)
{
    (*start) = NULL;
    (*current) = NULL;
    (*new_token) = NULL;
    return (lex_start);
}

void   *init_token(t_command *new_token)
{
    new_token->args = NULL;
    new_token->arc = 0;
    new_token->args_types = 0;
    new_token->input_redir = NULL;
    new_token->output_redir = NULL;
    new_token->pipe = 0;
    new_token->next = NULL;
    return (new_token);
}

void    make_token_list(t_command **start, t_command *new_token,
        t_command **current)
{
    if (!(*start))
        (*start) = new_token;
    else
        (*current)->next = new_token;
    (*current) = new_token;
}

t_command	*parser(t_token *lex_start)
{
    t_token     *lex_token;
    t_command   *start;
    t_command   *current;
    t_command   *new_token;

    lex_token = init_vars(lex_start, &start, &current, &new_token);
    while (lex_token)
    {
        new_token = malloc(sizeof(t_command));
        if (!new_token)
            return (free_command(start), NULL);
        init_token(new_token);
        if (pipe_tok(&lex_token, new_token)
            || pars_words(lex_token, &lex_token, new_token)
            || redir_tok(&lex_token, new_token))
        {
            if (new_token)
                free_command(new_token);
            if (start)
                free_command(start);
            return (NULL);
        }
        make_token_list(&start, new_token, &current);
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
