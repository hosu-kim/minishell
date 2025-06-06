/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/06 23:39:25 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*erase_dollar(const char *s)
{
	int		str_len;
	int		i;
    int     j;
	char	*dup;

	str_len = ft_strlen(s);
	dup = (char *)malloc((str_len) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
    j = 1;
	while (j < str_len)
	{
		dup[i] = s[j];
		i++;
        j++;
	}
	dup[i] = '\0';
	return (dup);
}

char    *environment_variable(char *arg, int j)
{
    int     i;
    int     k;
    int     l;
    char    *ptr;
    
    i = j;
    while(arg[i] != '\0' && !(arg[i] >= 9 && arg[i] <= 13) && arg[i] != ' ')
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

char    *make_var(char *arg, int start, int end, int len)
{
    char    *ptr;

    ptr = malloc(len * sizeof(char));
    if (!ptr)
        return (NULL);
    start++;
    len = 0;
    while (start < end)
    {
        ptr[len] = arg[start];
        start++;
        len++;
    }
    ptr[len] = '\0';
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

// char    *remake_token(char *start, char *var, char *end)
// {
//     int     i;
//     int     j;
//     int     k;
//     char    *ptr;

//     i = ft_strlen(start) + ft_strlen(var) + ft_strlen(end);
//     ptr = malloc((i + 1) * sizeof(char));
//     if (!ptr)
//         return (NULL);
//     j = 0;
//     while (j < i && start[j])
//     {
//         ptr[j] = start[j];
//         j++;
//     }
//     k = 0;
//     while (j < i && var[k])
//     {
//         ptr[j] = var[k];
//         j++;
//         k++;
//     }
//     k = 0;
//     while (j < i && end[k])
//     {
//         ptr[j] = end[k];
//         j++;
//         k++;
//     }
//     ptr[j] = '\0';
//     return (ptr);
// }

// void    expand_double_quotes(char **arg)
// {
//     int     i;
//     int     j;
//     char    *ptr;
//     char    *var;
//     char    *varvar;
//     char    *start;

//     i = 0;
//     while ((*arg)[i])
//     {
//         if ((*arg)[i] == '$')
//         {
//             j = i;
//             while ((*arg)[i] != '\0' && (*arg)[i] != 9 && (*arg)[i] != 13 && (*arg)[i] != ' ')
//                 i++;
//             start = start_of_env(*arg);
//             printf("start=> %s\n", start);
            
//             ptr = environment_variable(*arg, j);
//             printf("ptr=> %s\n", ptr);
            
//             var = make_var(*arg, j, i, (i - j));
//             printf("var=> %s\n", var);
            
//             varvar = getenv(var);
//             printf("varvar=> %s\n", varvar);
            
//             if (var)
//                 free(var);
//             free((*arg));
//             (*arg) = remake_token(start, varvar, ptr);
//         }
//     }
// }

void    update_token(char **arg, char *start, int j)
{
    int     i;
    int     l;
    char    *ptr;

    while ((*arg)[j] != '\0' && !((*arg)[j] >= 9 && (*arg)[j] <= 13) && (*arg)[j] != ' ')
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
    {
        ptr[l] = (*arg)[j];
        l++;
        j++;
    }
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

    while ((*arg)[j] != '\0' && !((*arg)[j] >= 9 && (*arg)[j] <= 13) && (*arg)[j] != ' ')
        j++;
    i = ft_strlen(start) + ft_strlen(var) + (ft_strlen(*arg) - j);
    ptr = malloc((i + 1) * sizeof(char));
    if (!ptr)
        return ;
    l = 0;
    while (l < i && start[l])
    {
        ptr[l] = start[l];
        l++;
    }
    m = 0;
    while (l < i && var[m])
    {
        ptr[l] = var[m];
        l++;
        m++;
    }
    while (l < i && (*arg)[j])
    {
        ptr[l] = (*arg)[j];
        l++;
        j++;
    }
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
    char    *original;
    char    *start;

    env = NULL;
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
                original = token->args[i];
                start = start_of_env(original);
                printf("startttt=> %s\n", start);
                env = environment_variable(original, j);
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
                    continue;
                }
                // env = erase_dollar(original);  // Extract variable name
                token->args[i] = ft_strdup(getenv(env));  // Get and duplicate env value
                free(original);  // Free the original
                free(env);  // Free the variable name
                free(start);
            }
            // For other types, keep the string as is (don't free it)
            i++;
        }
        token = token->next;
    }
}
