/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:02 by jakand            #+#    #+#             */
/*   Updated: 2025/05/18 22:47:47 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @details Used in ft_make_word_token(), ft_quotes(), ft_double_quotes()
 */
static char	*copy_token_str(const char *****input, int token_len)
{
	char	*token_value;
	int		i;

	i = 0;
	token_value = (char *)malloc((token_len + 1) * sizeof(char));
	if (!token_value)
		return (NULL);
	while (i < token_len)
	{
		token_value[i] = (****input)[i];
		i++;
	}
	token_value[i] = '\0';
	(****input) += token_len;
	return (token_value);
}

void	create_word_token_node(const char ****input, t_token *new_node, int len)
{
	new_node->type = T_WORD;
	new_node->value = copy_token_str(&input, len);
	new_node->next = NULL;
}

/**
 * @brief Stores sigle quote token data into a new node.
 * @details
 * 1. Skips first sigle quote character.
 * 2. Counts qouted_s_len (Length of quoted string) up to '\'' and '\0'.access
 * 3. Sets up the data into a new node 
 */
static int	create_single_quotes_node(const char ****input, t_token *new_node)
{
	int	quoted_s_len;

	quoted_s_len = 0;
	(***input)++;
	while ((***input)[quoted_s_len] != '\'' && (***input)[quoted_s_len] != '\0')
		quoted_s_len++;
	if ((***input)[quoted_s_len] == '\0')
		return (printf("Missing quote\n"), 1);
	new_node->type = T_Q_WORD;
	new_node->value = copy_token_str(&input, quoted_s_len);
	new_node->next = NULL;
	(***input)++;
	return (0);
}

static int	create_double_quotes_node(const char ****input, t_token *new_node)
{
	int	quoted_s_len;

	quoted_s_len = 0;
	(***input)++;
	while ((***input)[quoted_s_len] != 34 && (***input)[quoted_s_len] != '\0')
		quoted_s_len++;
	if ((***input)[quoted_s_len] == '\0')
		return (printf("Missing closing double quote\n"), 1);
	new_node->type = T_D_Q_WORD;
	new_node->value = copy_token_str(&input, quoted_s_len);
	new_node->next = NULL;
	(***input)++;
	return (0);
}


int	create_textual_token_node(const char ***input, t_token *new_token)
{
	int	i;

	i = 0;
	while ((**input)[i] != '\'' && (**input)[i] != '"' && (**input)[i] != ' '
		&& !((**input)[i] >= '\t' && (**input)[i] <= '\r') && (**input)[i] != '<'
		&& (**input)[i] != '>' && (**input)[i] != '|' && (**input)[i] != '\0')
	{
		if ((**input)[i] == '>' || (**input)[i] == '<' || (**input)[i] == '|')
		{
			printf("Missing space\n");
			return (1);
		}
		i++;
	}
	if (i != 0)
		return (create_word_token_node(&input, new_token, i), 0);
	if ((***input) == '\'')
		return (create_single_quotes_node(&input, new_token));
	if ((***input) == '"')
		return (create_double_quotes_node(&input, new_token));
	return (0);
}

