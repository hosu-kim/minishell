/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/07 19:25:44 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char    *environment_variable(char *arg, int j)
{
    int     i;
    int     k;
    int     l;
    char    *ptr;

    i = j;
    i++;
    while((arg[i] >= '0' && arg[i] <= '9') || (arg[i] >= 'a' && arg[i] <= 'z')
        || (arg[i] >= 'A' && arg[i] <= 'Z') || arg[i] == '_')
        i++;
    l = i - j;
    ptr = malloc((l) * sizeof(char));
    if (!ptr)
        return (NULL);
    k = 0;
    j++;
    while (j < i)
    {
        ptr[k] = arg[j];
        k++;
        j++;
    }
    ptr[k] = '\0';
    return (ptr);
}

char    *start_of_env(char *arg)
{
    int     i;
    int     j;
    char    *ptr;

    i = 0;
    while (arg[i] != '$')
        i++;
    ptr = malloc((i + 1) * sizeof(char));
    if (!ptr)
        return (NULL);
    j = 0;
    while (j < i)
    {
        ptr[j] = arg[j];
        j++;
    }
    ptr[j] = '\0';
    return (ptr);
}

void    update_token(char **arg, char *start, int j)
{
    int     i;
    int     l;
    char    *ptr;

    j++;
    while (((*arg)[j] >= '0' && (*arg)[j] <= '9')
        || ((*arg)[j] >= 'a' && (*arg)[j] <= 'z')
        || ((*arg)[j] >= 'A' && (*arg)[j] <= 'Z') || (*arg)[j] == '_')
        j++;
    i = ft_strlen(start) + (ft_strlen(*arg) - j);
    ptr = malloc((i + 1) * sizeof(char));
    if (!ptr)
        return ;
    l = 0;
    while (l < i && start[l])
    {
        ptr[l] = start[l];
        l++;
    }
    while (l < i && (*arg)[j])
        ptr[l++] = (*arg)[j++];
    ptr[l] = '\0';
    free((*arg));
    (*arg) = ptr;
}

void    remake_token(char **arg, char *start, char *var, int j)
{
    int     i;
    int     l;
    int     m;
    char    *ptr;

    j++;
    while (((*arg)[j] >= '0' && (*arg)[j] <= '9')
        || ((*arg)[j] >= 'a' && (*arg)[j] <= 'z')
        || ((*arg)[j] >= 'A' && (*arg)[j] <= 'Z') || (*arg)[j] == '_')
        j++;
    i = ft_strlen(start) + ft_strlen(var) + (ft_strlen(*arg) - j);
    ptr = malloc((i + 1) * sizeof(char));
    if (!ptr)
        return ;
    l = -1;
    while (++l < i && start[l])
        ptr[l] = start[l];
    m = 0;
    while (l < i && var[m])
        ptr[l++] = var[m++];
    while (l < i && (*arg)[j])
        ptr[l++] = (*arg)[j++];
    ptr[l] = '\0';
    free((*arg));
    (*arg) = ptr;
}

void    expand_token(t_command *token)
{
    int i;
    int j;
    char    *env;
    char    *var;
    char    *start;

    while(token)
    {
        i = 0;
        while (token->args && token->args[i] != NULL)
        {
            j = 0;
            while (token->args[i][j] != '$' && token->args[i][j] != '\0'
                    && (token->args_types[i] == 1 || token->args_types[i] == 2))
                j++;
            if (token->args[i][j] == '$' && token->args_types[i] != 0)
            {
                start = start_of_env(token->args[i]);
                printf("startttt=> %s\n", start);
                env = environment_variable(token->args[i], j);
                printf("envvvvv=> %s\n", env);
                var = getenv(env);
                printf("varrrr=> %s\n", var);
                if (var == NULL && token->args_types[i] == 1)
                {
                    token->args_types[i] = 3;
                    i++;
                    free(env);
                    free(start);
                    continue ;
                }
                else if (var == NULL && token->args_types[i] == 2)
                {
                    update_token(&token->args[i], start, j);
                    free(env);
                    free(start);
                    continue ;
                }
                else if (var && token->args_types[i] == 2)
                {
                    remake_token(&token->args[i], start, var, j);
                    free(env);
                    free(start);
                    continue ;
                }
                remake_token(&token->args[i], start, var, j);
                free(env);
                free(start);
            }
            i++;
        }
        token = token->next;
    }
}
