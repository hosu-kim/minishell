/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_textual_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:02 by jakand            #+#    #+#             */
/*   Updated: 2025/06/05 22:39:50 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @details Used in ft_make_word_token(), ft_quotes(), ft_double_quotes()
 */
static char	*extract_value(const char *****input, int token_len)
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

void	tokenize_word(const char ****input, t_token *new_node, int len)
{
	new_node->type = T_WORD;
	new_node->value = extract_value(&input, len);
	new_node->next = NULL;
}

/**
 * @brief Stores sigle quote token data into a new node.
 * @details
 * 1. Skips first sigle quote character.
 * 2. Counts qouted_s_len (Length of quoted string) up to '\'' and '\0'.access
 * 3. Sets up the data into a new node 
 */
static int	tokenize_single_quoted_text(const char ****input, t_token *new_node)
{
	int	quoted_s_len;

	quoted_s_len = 0;
	(***input)++;
	while ((***input)[quoted_s_len] != '\'' && (***input)[quoted_s_len] != '\0')
		quoted_s_len++;
	if ((***input)[quoted_s_len] == '\0')
		return (printf("Missing quote\n"), 1);
	new_node->type = T_Q_WORD;
	new_node->value = extract_value(&input, quoted_s_len);
	new_node->next = NULL;
	(***input)++;
	return (0);
}

static int	tokenize_double_quoted_text(const char ****input, t_token *new_node)
{
	int	quoted_s_len;

	quoted_s_len = 0;
	(***input)++;
	while ((***input)[quoted_s_len] != 34 && (***input)[quoted_s_len] != '\0')
		quoted_s_len++;
	if ((***input)[quoted_s_len] == '\0')
		return (printf("Missing closing double quote\n"), 1);
	new_node->type = T_D_Q_WORD;
	new_node->value = extract_value(&input, quoted_s_len);
	new_node->next = NULL;
	(***input)++;
	return (0);
}

int	tokenize_text(const char ***input, t_token *new_node)
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
		return (tokenize_word(&input, new_node, i), 0);
	if ((***input) == '\'')
		return (tokenize_single_quoted_text(&input, new_node));
	if ((***input) == '"')
		return (tokenize_double_quoted_text(&input, new_node));
	return (0);
}
