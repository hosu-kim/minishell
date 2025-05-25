/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_word_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:38:08 by jakand            #+#    #+#             */
/*   Updated: 2025/05/25 13:38:43 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
