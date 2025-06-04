/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/04 22:53:35 by jakand           ###   ########.fr       */
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

char    *end_of_token(char *arg, int j)
{
    int     i;
    int     k;
    char    *ptr;
    
    i = j;
    while(arg[i] != '\0')
        i++;
    i = i - j;
    ptr = malloc((i + 1) * sizeof(char));
    if (!ptr)
        return (NULL);
    k = 0;
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

char    *start_of_token(char *arg)
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
        ptr[j] = arg[i];
        i++;
        j++;
    }
    ptr[j] = '\0';
    return (ptr);
}

char    *remake_token(char *start, char *var, char *end)
{
    int     i;
    int     j;
    int     k;
    char    *ptr;

    i = ft_strlen(start) + ft_strlen(var) + ft_strlen(end);
    ptr = malloc((i + 1) * sizeof(char));
    if (!ptr)
        return (NULL);
    j = 0;
    while (j < i && start[j])
    {
        ptr[j] = start[j];
        j++;
    }
    k = 0;
    while (j < i && var[k])
    {
        ptr[j] = var[k];
        j++;
        k++;
    }
    k = 0;
    while (j < i && end[k])
    {
        ptr[j] = end[k];
        j++;
        k++;
    }
    ptr[j] = '\0';
    return (ptr);
}

void    expand_double_quotes(char **arg)
{
    int     i;
    int     j;
    char    *ptr;
    char    *var;
    char    *varvar;
    char    *start;

    i = 0;
    while ((*arg)[i])
    {
        if ((*arg)[i] == '$')
        {
            j = i;
            while ((*arg)[i] != '\0' && (*arg)[i] != 9 && (*arg)[i] != 13 && (*arg)[i] != ' ')
                i++;
            start = start_of_token(*arg);
            ptr = end_of_token(*arg, j);
            var = make_var(*arg, j, i, (i - j));
            varvar = getenv(var);
            printf("%s\n", varvar);
            if (var)
                free(var);
            free((*arg));
            (*arg) = remake_token(start, varvar, ptr);
        }
    }
}

void    expand_token(t_command *token)
{
    int i;
    char    *env;
    char    *original;

    env = NULL;
    while(token)
    {
        i = 0;
        while (token->args && token->args[i] != NULL)
        {
            if (token->args[i][0] == '$' && token->args_types[i] == 1)
            {
                original = token->args[i];  // Save the pointer
                env = erase_dollar(original);  // Extract variable name
                token->args[i] = ft_strdup(getenv(env));  // Get and duplicate env value
                free(original);  // Free the original
                free(env);  // Free the variable name
            }
            else if (token->args_types[i] == 2)
            {
                expand_double_quotes(&token->args[i]);
            }
            // For other types, keep the string as is (don't free it)
            i++;
        }
        token = token->next;
    }
}
