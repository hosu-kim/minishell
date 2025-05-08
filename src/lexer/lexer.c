/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:37 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/08 18:05:32 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_free_token(t_token *token)
{
	t_token		*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->value)
			free(temp->value);
		if (temp)
			free(temp);
	}
}

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

int		ft_space(const char **input)
{
	while (**input == ' ')
		(*input)++;
	if (**input == '\0')
		return (1);
	return (0);
}

void	ft_token_1(const char *input, t_token *new_token)
{
	if (*input == '|')
	{
		new_token->type = T_PIPE;
		new_token->value = ft_strdup("|");
	}
	else if (*input == '<' && input[1] != '<')
	{
		new_token->type = T_REDIR_IN;
		new_token->value = ft_strdup("<");
	}
	else if (*input == '>' && input[1] != '>')
	{
		new_token->type = T_REDIR_OUT;
		new_token->value = ft_strdup(">");
	}
}

void	ft_token_2(const char *input, t_token *new_token)
{
	if (input[0] == '<' && input[1] == '<')
	{
		new_token->type = T_HEREDOC;
		new_token->value = ft_strdup("<<");
	}
	else if (input[0] == '>' && input[1] == '>')
	{
		new_token->type = T_REDIR_APPEND;
		new_token->value = ft_strdup(">>");
	}
	new_token->next = NULL;
}

void	ft_make_token(const char *input, t_token *new_token, t_token **start, t_token **current)
{
	ft_token_1(input, new_token);
	ft_token_2(input, new_token);
	if (!(*start))
	{
		*start = new_token;
		*current = *start;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
}

t_token	*tokenize(const char *input)
{
	t_token		*start;
	t_token		*new_token;
	t_token		*current;

	start = NULL;
	new_token = NULL;
	current = NULL;
	while (*input != '\0')
	{
		if (ft_space(&input))
			break ;
		if (*input == '|' || *input == '>' || *input == '<')
		{
			new_token = malloc(sizeof(t_token));
			ft_make_token(input, new_token, &start, &current);
			if ((input[0] == '>' && input[1] == '>') || 
				(input[0] == '<' && input[1] == '<'))
				input += 2;
			else
				input++;
		}
		else
			input++;
	}
	return (start);
}
