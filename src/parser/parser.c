/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/22 21:27:43 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    free_command(t_command *cmd)
{
    t_redirection   *temp;
    t_redirection   *redir;
    int         i;

    if (!cmd)
        return ;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }
    redir = cmd->input_redir;
    while (redir)
    {
        temp = redir->next;
        free(redir->target);
        free(redir);
        redir = temp;
    }
    redir = cmd->output_redir;
    while (redir)
    {
        temp = redir->next;
        free(redir->target);
        free(redir);
        redir = temp;
    }
    if (cmd)
        free(cmd);
}

int     pars_words(t_token *lex_start, t_token **lex_token, t_command *new_token, int i)
{
    if (*lex_token)
    while (*lex_token && ((*lex_token)->type == T_WORD
        || (*lex_token)->type == T_Q_WORD || (*lex_token)->type == T_D_Q_WORD))
    {
        i++;
        *lex_token = (*lex_token)->next;
    }
    new_token->args = malloc((i + 1) * sizeof(char *));
    if (!new_token->args)
    {
        free_command(new_token);
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
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD && (*lex_token)->next->type
            != T_Q_WORD && (*lex_token)->next->type != T_D_Q_WORD))
            return (free_command(new_token), ("Syntax error\n"), 1);
        new_token->input_redir = malloc(sizeof(t_redirection));
        if (!new_token->input_redir)
        {
            free_command(new_token);
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
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD && (*lex_token)->next->type
            != T_Q_WORD && (*lex_token)->next->type != T_D_Q_WORD))
            return (free_command(new_token), ("Syntax error\n"), 1);
        new_token->output_redir = malloc(sizeof(t_redirection));
        if (!new_token->output_redir)
        {
            free_command(new_token);
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

int     append_tok(t_token **lex_token, t_command *new_token)
{
    if ((*lex_token) && (*lex_token)->type == T_REDIR_APPEND)
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD && (*lex_token)->next->type
            != T_Q_WORD && (*lex_token)->next->type != T_D_Q_WORD))
            return (free_command(new_token), ("Syntax error\n"), 1);
        new_token->output_redir = malloc(sizeof(t_redirection));
        if (!new_token->output_redir)
            return (free_command(new_token), 1);
        new_token->output_redir->type = TOK_APPEND;
        if ((*lex_token)->next)
            new_token->output_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_token->output_redir->target = NULL;
        new_token->output_redir->next = NULL;
    }
    else
        return (0);
    (*lex_token) = (*lex_token)->next;
    if ((*lex_token)->next)
        (*lex_token) = (*lex_token)->next;
    return (0);
}

int    heredoc_tok(t_token **lex_token, t_command *new_token)
{
    if ((*lex_token) && (*lex_token)->type == T_HEREDOC)
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD && (*lex_token)->next->type
            != T_Q_WORD && (*lex_token)->next->type != T_D_Q_WORD))
            return (free_command(new_token), ("Syntax error\n"), 1);
        new_token->input_redir = malloc(sizeof(t_redirection));
        if (!new_token->input_redir)
            return (free_command(new_token), 1);
        new_token->input_redir->type = TOK_HEREDOC;
        if ((*lex_token)->next)
            new_token->input_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_token->input_redir->target = NULL;
        new_token->input_redir->next = NULL;
    }
    else
        return (0);
    (*lex_token) = (*lex_token)->next;
    if ((*lex_token)->next)
        (*lex_token) = (*lex_token)->next;
    return (0);
}

void   *init_token(t_command *new_token)
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
    if (lex_token->type == T_PIPE)
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
        init_token(new_token);
        if (pars_words(lex_token, &lex_token, new_token, i)
            || input_tok(&lex_token, new_token)
            || output_tok(&lex_token, new_token)
            || append_tok(&lex_token, new_token)
            || heredoc_tok(&lex_token, new_token))
        {
            if (start)
                free_command(start);
            return (NULL);
        }
        if (!start)
            start = new_token;
        else
            current->next = new_token;
        current = new_token;

        if (lex_token && control_lex_token(lex_token))
            lex_token = lex_token->next;
    }
    return (start);
}
