/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:37 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/16 11:41:39 by hoskim           ###   ########seoul.kr  */
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


// name suggestion to 'skip_whitespaces' - Hosu 10/05/2025 16:17:56
// while (**input == ' ' || ('\t' <= *input && *input <= '\r'))
int		skip_whitespaces(const char **input)
{
	while (**input == ' ' || (**input >= 9 && **input <= 13))
		(*input)++;
	if (**input == '\0')
		return (1);
	return (0);
}
// name suggestion to 'single_char_tokens' - Hosu 10/05/2025 16:13:54
int	single_char_tokens(const char ***input, t_token *new_token)
{
	if (***input == '|')
	{
		new_token->type = T_PIPE;
		new_token->value = ft_strdup("|");
		(**input)++;
		return (1);
	}
	else if (***input == '<' && (**input)[1] != '<')
	{
		new_token->type = T_REDIR_IN;
		new_token->value = ft_strdup("<");
		(**input)++;
		return (1);
	}
	else if (***input == '>' && (**input)[1] != '>')
	{
		new_token->type = T_REDIR_OUT;
		new_token->value = ft_strdup(">");
		(**input)++;
		return (1);
	}
	return (0);
}

// name suggestion to 'double_char_tokens' - Hosu 10/05/2025 16:14:25
int	double_char_tokens(const char ***input, t_token *new_token)
{
	if (***input == '<' && (**input)[1] == '<')
	{
		new_token->type = T_HEREDOC;
		new_token->value = ft_strdup("<<");
		(**input) += 2;
		new_token->next = NULL;
		return (1);
	}
	else if (***input == '>' && (**input)[1] == '>')
	{
		new_token->type = T_REDIR_APPEND;
		new_token->value = ft_strdup(">>");
		(**input) += 2;
		new_token->next = NULL;
		return (1);
	}
	return (0);
}

char	*ft_make_tok(const char *****input, int i)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = (****input)[j];
		j++;
	}
	str[j] = '\0';
	(****input) += i;
	return (str);
}

void	ft_make_word_token(const char ****input, t_token *new_token, int i)
{
	new_token->type = T_WORD;
	new_token->value = ft_make_tok(&input, i);
	new_token->next = NULL;
}

int	ft_quotes(const char ****input, t_token *new_token, int i)
{
	i = 0;
	if ((***input)[i] == 39)
	{
		(***input)++;
		while ((***input)[i] != 39 && (***input)[i] != '\0')
			i++;
	}
	else
	{
		(***input)++;
		while ((***input)[i] != 34 && (***input)[i] != '\0')
			i++;
	}
	if ((***input)[i] == '\0')
		return (printf("Missing quote\n"), 1);
	new_token->type = T_WORD;
	new_token->value = ft_make_tok(&input, i);
	new_token->next = NULL;
	(***input)++;
	return (0);
}

int	char_tokens(const char ***input, t_token *new_token)
{
	int		i;

	i = 0;
	while ((**input)[i] != 39 && (**input)[i] != 34 && (**input)[i] != ' '
		&& !((**input)[i] >= 9 && (**input)[i] <= 13) && (**input)[i] != '\0')
	{
		if ((**input)[i] == '>' || (**input)[i] == '<' || (**input)[i] == '|')
		{
			printf("Missing space\n");
			return (1);
		}
		i++;
	}
	if (i != 0)
		return (ft_make_word_token(&input, new_token, i), 0);
	if ((***input) == 39)
		return (ft_quotes(&input, new_token, i));
	if ((***input) == 34)
		return (ft_quotes(&input, new_token, i));
	return (0);
}

// name suggestion to add_new_token or link_new_token - Hosu 10/05/25 16:35:22
int	add_new_token(const char **input, t_token *new_token, t_token **start, t_token **current)
{
	if (!single_char_tokens(&input, new_token))
	{
		if (!double_char_tokens(&input, new_token))
			if (char_tokens(&input, new_token))
				return (1);
	}
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
	return (0);
}

/* Please implement these:
   1. Tokenizing other words as T_WORD
   2. If the function finds " or ', it stores the whole string in a node as type T_WORD
   ex) a_node = {type: T_WORD, *value: "this is an example", *next}
   - Hosu 10/05/2025 20:32:55
*/
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
		if (skip_whitespaces(&input))
			break ;
		new_token = malloc(sizeof(t_token));
		if (new_token)
		{
			new_token->type = 0;
			new_token->value = NULL;
			new_token->next = NULL;
		}
		if (add_new_token(&input, new_token, &start, &current))
		{
			ft_free_token(new_token);
			ft_free_token(start);
			return (NULL);
		}
	}
	return (start);
}
