/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/24 23:35:13 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    free_args(t_command *start)
{
    int     i;

    i = 0;
    if (start->args)
    {
        i = 0;
        while (start->args[i])
        {
            free(start->args[i]);
            i++;
        }
        free(start->args);
    }
}

void    free_input_redir(t_redirection *redir)
{
    t_redirection *temp;
    
    while (redir)
    {
        temp = redir->next;
        free(redir->target);
        free(redir);
        redir = temp;
    }
}

void    free_output_redir(t_redirection *redir)
{
    t_redirection *temp;
    
    while (redir)
    {
        temp = redir->next;
        free(redir->target);
        free(redir);
        redir = temp;
    }
}

void    free_command(t_command *start)
{
    t_command       *cmd;
    t_redirection   *redir;

    if (!start)
        return ;
    cmd = start;
    while (start)
    {
        cmd = start->next;
        free_args(start);
        redir = start->input_redir;
        if (redir)
            free_input_redir(redir);
        redir = start->output_redir;
        if (redir)
            free_output_redir(redir);
        free(start);
        start = cmd;
    }
}

int     pars_words(t_token *lex_start, t_token **lex_token,
        t_command *new_token)
{
    int     i;
    
    i = 0;
    while (*lex_token && ((*lex_token)->type == T_WORD
        || (*lex_token)->type == T_Q_WORD || (*lex_token)->type == T_D_Q_WORD))
    {
        i++;
        *lex_token = (*lex_token)->next;
    }
    new_token->args = malloc((i + 1) * sizeof(char *));
    if (!new_token->args)
        return (1);
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
    t_redirection *new_redir;
    t_redirection *current;
    
    if (*lex_token && ((*lex_token)->type == T_REDIR_IN))
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
            && (*lex_token)->next->type != T_Q_WORD
            && (*lex_token)->next->type != T_D_Q_WORD))
            return (printf("Syntax error\n"), 1);
        
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (1);
        
        new_redir->type = TOK_INPUT;
        if ((*lex_token)->next)
            new_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_redir->target = NULL;
        new_redir->next = NULL;
        
        // Chain the redirection instead of overwriting
        if (!new_token->input_redir)
        {
            new_token->input_redir = new_redir;
        }
        else
        {
            current = new_token->input_redir;
            while (current->next)
                current = current->next;
            current->next = new_redir;
        }
    }
    else
        return (0);
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    return (0);
}

int    heredoc_tok(t_token **lex_token, t_command *new_token)
{
    t_redirection *new_redir;
    t_redirection *current;
    
    if ((*lex_token) && (*lex_token)->type == T_HEREDOC)
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
            && (*lex_token)->next->type != T_Q_WORD
            && (*lex_token)->next->type != T_D_Q_WORD))
            return (printf("Syntax error\n"), 1);
        
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (1);
        
        new_redir->type = TOK_HEREDOC;
        if ((*lex_token)->next)
            new_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_redir->target = NULL;
        new_redir->next = NULL;
        
        // Chain the redirection instead of overwriting
        if (!new_token->input_redir)
        {
            new_token->input_redir = new_redir;
        }
        else
        {
            current = new_token->input_redir;
            while (current->next)
                current = current->next;
            current->next = new_redir;
        }
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
    t_redirection *new_redir;
    t_redirection *current;
    
    if ((*lex_token) && (*lex_token)->type == T_REDIR_OUT)
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
            && (*lex_token)->next->type != T_Q_WORD
            && (*lex_token)->next->type != T_D_Q_WORD))
            return (printf("Syntax error\n"), 1);
        
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (1);
        
        new_redir->type = TOK_OUTPUT;
        if ((*lex_token)->next)
            new_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_redir->target = NULL;
        new_redir->next = NULL;
        
        // Chain the redirection instead of overwriting
        if (!new_token->output_redir)
        {
            new_token->output_redir = new_redir;
        }
        else
        {
            current = new_token->output_redir;
            while (current->next)
                current = current->next;
            current->next = new_redir;
        }
    }
    else
        return (0);
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    if ((*lex_token))
        (*lex_token) = (*lex_token)->next;
    return (0);
}

int     redir_tok(t_token **lex_token, t_command *new_token)
{
    t_redirection *new_redir;
    t_redirection *current;
    
    while ((*lex_token) && (*lex_token)->type != T_PIPE && ((*lex_token)->type == T_REDIR_IN
        || (*lex_token)->type == T_REDIR_OUT || (*lex_token)->type == T_REDIR_APPEND
        || (*lex_token)->type == T_HEREDOC))
    {
        if ((*lex_token)->next == NULL || ((*lex_token)->next->type != T_WORD
            && (*lex_token)->next->type != T_Q_WORD
            && (*lex_token)->next->type != T_D_Q_WORD))
            return (printf("Syntax error\n"), 1);
        new_redir = malloc(sizeof(t_redirection));
        if (!new_redir)
            return (1);
        if ((*lex_token)->type == T_REDIR_IN)
            new_redir->type = TOK_INPUT;
        if ((*lex_token)->type == T_REDIR_OUT)
            new_redir->type = TOK_OUTPUT;
        if ((*lex_token)->type == T_REDIR_APPEND)
            new_redir->type = TOK_APPEND;
        if ((*lex_token)->type == T_HEREDOC)
            new_redir->type = TOK_HEREDOC;
        if ((*lex_token)->next)
            new_redir->target = ft_strdup((*lex_token)->next->value);
        else
            new_redir->target = NULL;
        new_redir->next = NULL;
        if ((*lex_token)->type == T_REDIR_IN || (*lex_token)->type == T_HEREDOC)
        {
            if (!new_token->input_redir)
            {
                new_token->input_redir = new_redir;
            }
            else
            {
                current = new_token->input_redir;
                while (current->next)
                    current = current->next;
                current->next = new_redir;
            }
            }
            if ((*lex_token)->type == T_REDIR_OUT || (*lex_token)->type == T_REDIR_APPEND)
            {
            if (!new_token->output_redir)
            {
                new_token->output_redir = new_redir;
            }
            else
            {
                current = new_token->output_redir;
                while (current->next)
                    current = current->next;
                current->next = new_redir;
            }
        }
        if ((*lex_token))
            (*lex_token) = (*lex_token)->next;
        if ((*lex_token))
            (*lex_token) = (*lex_token)->next;
    }
    return (0);
}

int     pipe_tok(t_token **lex_token, t_command *new_token)
{
    if (!(*lex_token) || (*lex_token)->type != T_PIPE)
        return (0);
    if ((*lex_token)->next == NULL || (*lex_token)->next->type == T_PIPE)
        return (printf("Syntax error\n"), 1);
    if ((*lex_token)->next->type != T_WORD
        && (*lex_token)->next->type != T_Q_WORD
        && (*lex_token)->next->type != T_D_Q_WORD)
        return (printf("Syntax error\n"), 1);
    (*lex_token) = (*lex_token)->next;
    new_token->pipe = 1;
    return (0);
}

void   *init_token(t_command *new_token)
{
    new_token->args = NULL;
    new_token->arc = 0;
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

t_token     *init_vars(t_token *lex_start, t_command **start,
                t_command **current, t_command **new_token)
{
    (*start) = NULL;
    (*current) = NULL;
    (*new_token) = NULL;
    return (lex_start);
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
