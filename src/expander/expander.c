/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/05/27 23:43:24 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void    expand_token(t_command *token)
{
    int i;

    while(token)
    {
        i = 0;
        while (token->args && token->args[i] != NULL)
        {
            free(token->args[i]);
            token->args[i] = getenv("HOME");
            i++;
        }
        token = token->next;
    }
}
