/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:37 by jakand            #+#    #+#             */
/*   Updated: 2025/06/04 10:00:47 by hoskim           ###   ########seoul.kr  */
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

void    expand_token(t_command *token)
{
	int i;
	char    *env;

	env = NULL;
	while(token)
	{
		i = 0;
		while (token->args && token->args[i] != NULL)
		{
			free(token->args[i]);
			if (token->args[i][0] == '$' && token->args_types != 0)
			{
				env = erase_dollar(token->args[i]);
				token->args[i] = getenv(env);
				free(env);
			}
			i++;
		}
		token = token->next;
	}
}
