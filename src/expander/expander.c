/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/08 00:25:39 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*start_of_env(char *arg)
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

char	*environment_variable(char *arg, int j)
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

void	free_var(char **env, char **var)
{
	if (*env)
		free(*env);
	if (*var)
		free(*var);
}

int	make_env(t_command **token, int i, int j)
{
	char    *env;
    char    *var;
    char    *start;

	start = start_of_env((*token)->args[i]);
    env = environment_variable((*token)->args[i], j);
    var = getenv(env);
    printf("startttt=> %s\nenvvvvv=> %s\nvarrrr=> %s\n", start, env, var);
    if (var == NULL && (*token)->args_types[i] < 3)
    {
		update_token(&(*token)->args[i], start, j);
		if ((*token)->args[i][0] == '\0')
			(*token)->args_types[i] = 3;
		free_var(&env, &start);
        return (1);
    }
    else if (var)
    {
        remake_token(&(*token)->args[i], start, var, j);
		free_var(&env, &start);
        return (1);
    }
	free_var(&env, &start);
	return (0);
}

void	expand_token(t_command *token)
{
    int i;
    int j;
	
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
                if (make_env(&token, i, j) == 1)
					continue ;
            }
            i++;
        }
        token = token->next;
    }
}
