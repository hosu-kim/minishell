/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/18 23:03:54 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int     pars_words(t_token *start, t_token **current, t_command *token, int i)
{
    while (*current && ((*current)->type == T_WORD
        || (*current)->type == T_Q_WORD || (*current)->type == T_D_Q_WORD))
    {
        i++;
        *current = (*current)->next;
    }
    token->args = malloc((i + 1) * sizeof(char *));
    if (!token->args)
    {
        free(token);
        return (1);
    }
    *current = start;
    i = 0;
    while (*current && ((*current)->type == T_WORD
        || (*current)->type == T_Q_WORD || (*current)->type == T_D_Q_WORD))
    {
        token->args[i] = ft_strdup((*current)->value);
        i++;
        *current = (*current)->next;
    }
    token->args[i] = NULL;
    token->arc = i;

    return (0);
}

int     input_tok(t_token **current, t_command *token)
{
    if (*current && ((*current)->type == T_REDIR_IN))
    {
        token->input_redir->type = TOK_INPUT;
        if ((*current)->next)
            token->input_redir->target = ft_strdup((*current)->next->value);
        else
            token->input_redir->target = NULL;
        token->input_redir->next = NULL;
    }
    else
        return (1);
    if ((*current))
        (*current) = (*current)->next;
    if ((*current))
        (*current) = (*current)->next;
    return (0);
}

int    output_tok(t_token **current, t_command *token)
{
    if ((*current) && (*current)->type == T_REDIR_OUT)
    {
        token->output_redir->type = TOK_OUTPUT;
        if ((*current)->next)
            token->output_redir->target = ft_strdup((*current)->next->value);
        else
            token->output_redir->target = NULL;
        token->output_redir->next = NULL;
    }
    else
        return (1);
    if ((*current))
        (*current) = (*current)->next;
    if ((*current))
        (*current) = (*current)->next;
    return (0);
}

t_command	*parser(t_token *start)
{
    t_token     *current;
    t_command   *token;
    // t_command   *new_token;
    int         i;

    token = malloc(sizeof(t_command));
    token->input_redir = malloc(sizeof(t_redirection));
    token->output_redir = malloc(sizeof(t_redirection));
    if (token->input_redir)
    {
        token->input_redir->target = NULL;
        token->input_redir->type = 0;
        token->input_redir->next = NULL;
    }

    if (token->output_redir)
    {
        token->output_redir->target = NULL;
        token->output_redir->type = 0;
        token->output_redir->next = NULL;
    }

    if (!token)
        return (NULL);
    current = start;
    i = 0;
    while (1)
    {
        if (pars_words(start, &current, token, i))
            break ;
        if (!input_tok(&current, token))
        {
            if (!output_tok(&current, token))
                break ;
        }
        // if (current->type == T_PIPE)
        // {
        //     start = current->next;
            
        // }
        // printf("%s\n", current->value);
        break ;
    }
    token->next = NULL;
    return (token);
}
