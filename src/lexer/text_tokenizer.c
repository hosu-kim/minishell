/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:02 by jakand            #+#    #+#             */
/*   Updated: 2025/06/20 20:03:39 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

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

/**
 * @brief Tokenizes a single quoted text as a node.
 * @details
 * 1. Skips first single quote character.
 * 2. Counts quoted_s_len (Length of quoted string) up to '\'' and '\0'.
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
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 41);
		return (FAILURE);
	}
	new_node->type = T_Q_WORD;
	new_node->value = extract_value(&input, quoted_s_len);
	new_node->next = NULL;
	(***input)++;
	return (SUCCESS);
}

/**
 * @brief Tokenizes a double quoted text as a node.
 */
static int	tokenize_double_quoted_text(const char ****input, t_token *new_node)
{
	int	quoted_s_len;

	quoted_s_len = 0;
	(***input)++;
	while ((***input)[quoted_s_len] != 34 && (***input)[quoted_s_len] != '\0')
		quoted_s_len++;
	if ((***input)[quoted_s_len] == '\0')
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 41);
		return (FAILURE);
	}
	new_node->type = T_D_Q_WORD;
	new_node->value = extract_value(&input, quoted_s_len);
	new_node->next = NULL;
	(***input)++;
	return (SUCCESS);
}

static void	tokenize_word(const char ****input, t_token *new_node, int len)
{
	new_node->type = T_WORD;
	new_node->value = extract_value(&input, len);
	new_node->next = NULL;
}

int	text_tokenizer(const char ***input, t_token *new_node)
{
	int	i;

	i = 0;
	while ((**input)[i] != '\'' && (**input)[i] != '"' && (**input)[i] != ' '
		&& !((**input)[i] >= '\t' && (**input)[i] <= '\r') && (**input)[i] != '<'
		&& (**input)[i] != '>' && (**input)[i] != '|' && (**input)[i] != '\0')
	{
		if ((**input)[i] == '>' || (**input)[i] == '<' || (**input)[i] == '|')
		{
			write(STDERR_FILENO,\
				"minishell: syntax error near unexpected token\n", 47);
			return (FAILURE);
		}
		i++;
	}
	if (i != 0)
		return (tokenize_word(&input, new_node, i), 0);
	if ((***input) == '\'')
		return (tokenize_single_quoted_text((const char ****)&input, new_node));
	if ((***input) == '"')
		return (tokenize_double_quoted_text((const char ****)&input, new_node));
	return (SUCCESS);
}
