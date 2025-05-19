/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/19 21:49:50 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int     pars_words(t_token *lex_start, t_token **lex_token, t_command *new_token, int i)
{
    while (*lex_token && ((*lex_token)->type == T_WORD
        || (*lex_token)->type == T_Q_WORD || (*lex_token)->type == T_D_Q_WORD))
    {
        i++;
        *lex_token = (*lex_token)->next;
    }
    new_token->args = malloc((i + 1) * sizeof(char *));
    if (!new_token->args)
    {
        free(new_token);
        return (1);
    }
    *lex_token = lex_start;
    i = 0;
    while (*lex_token && ((*lex_token)->type == T_WORD
        || (*lex_token)->type == T_Q_WORD || (*lex_token)->type == T_D_Q_WORD))
    {
        new_token->args[i] = ft_strdup((*lex_token)->value);
        i++;
        *lex_token = (*lex_token)->next;
    }
    new_token->args[i] = NULL;
    new_token->arc = i;

    return (0);
}

int     input_tok(t_token **lex_token, t_command *new_token)
{
    if (*lex_token && ((*lex_token)->type == T_REDIR_IN))
    {
        new_token->input_redir = malloc(sizeof(t_redirection));
        if (!new_token->input_redir)
        {
            free(new_token);
            return (1);
        }
        new_token->input_redir->type = TOK_INPUT;
        if ((*lex_token)->next)
            new_token->input_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_token->input_redir->target = NULL;
        new_token->input_redir->next = NULL;
    }
    else
        return (0);
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    return (0);
}

int    output_tok(t_token **lex_token, t_command *new_token)
{
    if ((*lex_token) && (*lex_token)->type == T_REDIR_OUT)
    {
        new_token->output_redir = malloc(sizeof(t_redirection));
        if (!new_token->output_redir)
        {
            free(new_token);
            return (1);
        }
        new_token->output_redir->type = TOK_OUTPUT;
        if ((*lex_token)->next)
            new_token->output_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_token->output_redir->target = NULL;
        new_token->output_redir->next = NULL;
    }
    else
        return (0);
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    return (0);
}

t_command   *init_token(t_command *new_token)
{
    new_token->args = NULL;
    new_token->arc = 0;
    new_token->input_redir = NULL;
    new_token->output_redir = NULL;
    new_token->next = NULL;
    return (new_token);
}

int     control_lex_token(t_token *lex_token)
{
    if (lex_token->type == T_REDIR_IN || lex_token->type == T_REDIR_OUT
        || lex_token->type == T_REDIR_APPEND || lex_token->type == T_HEREDOC
        || lex_token->type == T_PIPE)
        return (1);
    return (0);
}

t_command	*parser(t_token *lex_start)
{
    t_token     *lex_token;
    t_command   *start;
    t_command   *current;
    t_command   *new_token;
    int         i;

    lex_token = lex_start;
    start = NULL;
    current = NULL;
    new_token = NULL;
    while (lex_token)
    {
        i = 0;
        new_token = malloc(sizeof(t_command));
        if (!new_token)
            return (NULL);
        new_token = init_token(new_token);
        if (pars_words(lex_token, &lex_token, new_token, i))
            break ;
        if (input_tok(&lex_token, new_token))
            break ;
        if (output_tok(&lex_token, new_token))
            break ;
        if (!start)
        {
            start = new_token;
        }
        else
        {
            current->next = new_token;
        }
        current = new_token;

        if (lex_token && control_lex_token(lex_token))
        {
            lex_token = lex_token->next;
        }
    }
    return (start);
}
    // token = NULL;
    // current = start;
    // i = 0;
    // while (1)
    // {
    //     if (token)
    //     {
    //         new_token = malloc(sizeof(t_command));
    //         if (!new_token)
    //             return (NULL);
    //         token = token->next;
    //         new_token = token;
    //     }
    //     else
    //         token = malloc(sizeof(t_command));
    //     if (!token)
    //         return (NULL);
    //     token->next = NULL;
        
    //     token = input_tok(&current, token);
    //     token = output_tok(&current, token);

    //     break ;
    // }
    // return (token);
// }
