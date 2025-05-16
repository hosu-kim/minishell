/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:02 by jakand            #+#    #+#             */
/*   Updated: 2025/05/16 20:43:25 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	(***input)++;
	while ((***input)[i] != 39 && (***input)[i] != '\0')
		i++;
	if ((***input)[i] == '\0')
		return (printf("Missing quote\n"), 1);
	new_token->type = T_WORD;
	new_token->value = ft_make_tok(&input, i);
	new_token->next = NULL;
	(***input)++;
	return (0);
}

int	ft_double_quotes(const char ****input, t_token *new_token, int i)
{
	i = 0;
	(***input)++;
	while ((***input)[i] != 34 && (***input)[i] != '\0')
		i++;
	if ((***input)[i] == '\0')
		return (printf("Missing double quote\n"), 1);
	new_token->type = T_D_Q_WORD;
	new_token->value = ft_make_tok(&input, i);
	new_token->next = NULL;
	(***input)++;
	return (0);
}

int	char_tokens(const char ***input, t_token *new_token)
{
	int		i;

	i = 0;
	while ((**input)[i] != 39 && (**input)[i] != 34 && (**input)[i] != 32
		&& !((**input)[i] >= 9 && (**input)[i] <= 13) && (**input)[i] != 60
		&& (**input)[i] != 62 && (**input)[i] != 124 && (**input)[i] != '\0')
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
		return (ft_double_quotes(&input, new_token, i));
	return (0);
}
