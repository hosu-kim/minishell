/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:37 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/06 20:32:42 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*ptr;

	i = ft_strlen(s);
	j = 0;
	ptr = (char *) malloc((i + 1) * sizeof (char));
	if (!ptr)
		return (NULL);
	while (j < i)
	{
		ptr[j] = s[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

t_token	*tokenize(const char *input)
{
	t_token		*start;
	t_token		*new_token;
	t_token		*current;

	start = NULL;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	while (*input != '\0')
	{
		while (*input == ' ')
			input++;
		if (*input == '|')
		{
			new_token->type = T_PIPE;
			new_token->value = ft_strdup("|");
			new_token->next = NULL;
		}
		if (!start)
			start = new_token;
		else
		{
			current = start;
			while (current->next)
				current = current->next;
			current->next = new_token;
		}
	}
	return (start);
}

// void	free_tokens(t_token *head)
// {
// 	t_token	*tmp;

// 	while (head)
// 	{
// 		tmp = head->next;
// 		free(head->value);
// 		free(head);
// 		head = tmp;
// 	}
// }
